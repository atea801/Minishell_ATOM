# PLAN COMPLET : GESTION AVANCÉE DES QUOTES

## 📊 ANALYSE DE L'ARCHITECTURE ACTUELLE

### Flux existant (à préserver) :
```
Input → parsing_1() → tokenizer() → parsing_2() → expansion → built-ins
```

### Points d'amélioration identifiés :
1. `valide_quote()` : validation trop simple
2. `quote_gestion.c` : logique complexe avec marqueurs
3. `expand_utils.c` : recalcul permanent
4. Pas de gestion des échappements

## 🚀 PHASE 1 : FONDATIONS (Validation robuste)

### Objectif : Remplacer valide_quote() par une validation complète

#### Fichiers créés :
- `src/parsing_1/quote_validator.c`
- `src/parsing_1/quote_validator.h`

#### Structures nouvelles :
```c
typedef enum e_quote_state {
    STATE_NORMAL = 0,
    STATE_SINGLE_QUOTE = 1,
    STATE_DOUBLE_QUOTE = 2,
    STATE_ESCAPED = 3
} t_quote_state;

typedef struct s_quote_context {
    t_quote_state current_state;
    t_quote_state prev_state;
    int error_pos;
    char *error_msg;
} t_quote_context;
```

#### Fonctions à implémenter :
```c
// Remplace directement valide_quote()
int validate_quotes_complete(char *input);

// Nouvelles fonctions de diagnostic
t_quote_context *analyze_quotes(char *input);
char *get_quote_error_message(t_quote_context *ctx);
void free_quote_context(t_quote_context *ctx);
```

#### Cas gérés :
- ✅ Quotes non fermées : `echo "hello`
- ✅ Échappements doubles : `echo "hello \"world\""`
- ✅ Échappements simples : `echo 'can'\''t'`
- ✅ Imbrications : `echo "outer 'inner' text"`
- ✅ Caractères spéciaux : `echo "path with spaces"`

## 🔧 PHASE 2 : TOKENIZATION INTELLIGENTE

### Objectif : Éliminer __SINGLE_QUOTE__ et améliorer quote_gestion.c

#### Fichiers modifiés :
- `src/tokenizer_1/quote_engine.c` (nouveau)
- `src/tokenizer_1/quote_gestion.c` (amélioré)

#### Nouvelles structures :
```c
typedef struct s_token_quote_info {
    char *raw_content;      // Contenu avec quotes
    char *clean_content;    // Contenu sans quotes
    t_quote_state quote_type;
    bool needs_expansion;
    bool is_literal;
} t_token_quote_info;
```

#### Améliorations :
- ✅ Plus de marqueurs __SINGLE_QUOTE__
- ✅ Information de contexte préservée
- ✅ Gestion des cas mixtes : `"text 'inside' more"`
- ✅ Préparation pour l'expansion intelligente

## ⚡ PHASE 3 : EXPANSION OPTIMISÉE

### Objectif : Éviter le recalcul des positions de quotes

#### Fichiers créés/modifiés :
- `src/env/quote_expansion_map.c` (nouveau)
- `src/env/check_expandable/expand_utils.c` (optimisé)

#### Nouvelle approche :
```c
typedef struct s_quote_map {
    char *quote_states;     // Array des états par position
    int length;
    bool has_variables;     // Optimisation : contient des $VAR ?
} t_quote_map;
```

#### Optimisations :
- ✅ Calcul une fois, utilisation multiple
- ✅ Performance O(n) au lieu de O(n²)
- ✅ Cache intelligent pour les variables
- ✅ Expansion contextuelle précise

## 🧪 PHASE 4 : CAS AVANCÉS

### Objectif : Gérer les cas les plus complexes de bash

#### Cas avancés gérés :
```bash
# Échappements complexes
echo "hello \"world\" with \\backslash"

# Variables dans quotes
echo "User is $USER in '$PWD'"

# Quotes imbriquées
echo "outer \"inner \\\"deep\\\" inner\" outer"

# Cas mixtes
cmd "arg with 'single'" 'arg with "double"' normal_arg

# Heredoc avec quotes
cat << "EOF"
content with 'quotes'
EOF

# Redirections avec espaces
echo "hello" > "file with spaces.txt"
```

## 📈 PHASE 5 : TESTS ET VALIDATION

### Objectif : S'assurer que tout fonctionne parfaitement

#### Suite de tests :

## 🔄 STRATÉGIE D'IMPLÉMENTATION

### Approche progressive :
1. **Développement parallèle** : Nouveau code sans toucher l'ancien
2. **Tests intensifs** : Validation avant remplacement
3. **Switch progressif** : Fonction par fonction
4. **Rollback facile** : Garde de l'ancien code temporairement

### Points de validation :

## 📝 DÉTAILS TECHNIQUES PAR PHASE
```markdown
[Voir sections détaillées ci-dessous]
```

## 🕰️ Historique des modifications (résumé pour revue)

Date: 2025-11-18

Résumé rapide :
- Objectif principal : Remplacer le mécanisme ancien basé sur le préfixe magique `__SINGLE_QUOTE__` par une déclaration explicite du type de quote directement dans la structure `t_token`.
- Pourquoi : le préfixe ajoutait de la complexité, des manipulations de chaînes fragiles (décalage +16), et rendait le code difficile à maintenir et à étendre.

Fichiers modifiés / ajoutés :
- `atom.h` : ajout du champ `int quote_type` dans `t_token` (0=normal,1=single,2=double).
- `src/init.c` : initialisation de `quote_type` dans `init_token_1_only()` et `init_token_struct()`.
- `src/tokenizer_1/token_utils.c` : ajout de `put_token_with_quote()` et initialisation systématique de `quote_type`.
- `src/tokenizer_1/quote_gestion.c` : suppression du préfixe `__SINGLE_QUOTE__`, détection et propagation de `quote_type` via `put_token_with_quote()`.
- `src/parsing_2/tokenizer_2/token_2_find_type.c` : suppression de la détection par `ft_strnstr("__SINGLE_QUOTE__")` et adaptation pour utiliser `t_token->quote_type`.

Tests et validation effectués :
- Compilation complète (make) : OK
- Tests manuels principaux exécutés et comparés au comportement POSIX de bash :
    - `echo 'hello world'` (simple quotes, pas d'expansion)
    - `echo "hello $USER"` (double quotes, expansion attendue)
    - `echo 'hello $USER'` (single quotes, pas d'expansion)
    - `echo "He said 'hi'"` (nested single inside double)
    => Résultat : comportement identique à bash pour ces cas.

Notes explicatives pour ton mate (comment expliquer les changements)
- Contexte : Le code précédent préfixait les tokens issus de quotes simples par une chaîne spéciale `__SINGLE_QUOTE__` pour indiquer qu'il ne fallait pas étendre les variables. C'était une solution pragmatique, mais fragile et peu explicite.
- Ce que j'ai fait : J'ai fait passer cette information directement dans la structure `t_token` (champ `quote_type`). Le tokenizer met maintenant `quote_type` lors de la création du token. Plus besoin d'annoter la chaîne de caractères elle-même.
- Pourquoi c'est mieux :
    1. Lisibilité : la présence d'un entier explicite est plus claire qu'un préfixe magique.
    2. Robustesse : on évite les offsets et la nécessité de découper la chaîne (`+16`).
    3. Extensibilité : il est facile d'ajouter d'autres états (ex : échappement, heredoc) sans toucher au contenu du token.
    4. Séparation des responsabilités : le token contient son contenu, le meta-info (quote_type) est séparé.
- Impact limité : J'ai uniquement adapté les endroits où on détectait auparavant le marqueur (principalement `token_2_find_type.c`) et l'émission des tokens (tokenizer). Les autres étapes (parsing, expansion) n'ont pas besoin de connaître le marqueur.

Choses à surveiller / risques connus
- Vérifier les cas rares : combinaisons complexes d'échappements et heredocs — déjà prévus dans la suite de tests, mais à surveiller.
- API : si un plugin ou un autre module consommait la chaîne préfixée, il faudra l'adapter. Recherche rapide montre aucune dépendance active au préfixe dans le code.

Rollback / debug rapide
- Pour revenir en arrière rapidement : remettre les modifications dans `quote_gestion.c` (réintroduire le préfixe) et restaurer les usages originaux dans `token_2_find_type.c`. Git facilite le revert si nécessaire.
- Debug : activer les impressions temporaires via `print_token_list()` pour visualiser `t_token->value` et `t_token->quote_type` pendant le parsing/tokenization.

Prochaines actions recommandées
- Intégrer ces changements dans une branche dédiée et ouvrir une MR avec ce changelog.
- Lancer la suite de tests automatique `minishell_tester/` pour détecter toutes régressions.
- Ajouter 3-4 tests unitaires automatisés (scripts) pour les cas de quotes listés ci-dessus et les inclure dans CI.

---