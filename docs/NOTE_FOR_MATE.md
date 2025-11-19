Note courte pour la revue technique (à destination de ton collègue)

Contexte
-------
Le code utilisait auparavant un préfixe magique `__SINGLE_QUOTE__` collé au début des tokens issus de quotes simples pour signaler "ne pas expander". C'était pragmatique mais fragile (décalages hardcodés, parsing difficile à suivre).

Changements principaux
---------------------
- Remplacement du préfixe magique par un champ explicite `quote_type` dans la structure `t_token`.
  - Valeurs : 0 = normal, 1 = simple quote, 2 = double quote
- Ajout d'une API de création de token qui prend en charge `quote_type` : `put_token_with_quote()`.
- `quote_gestion.c` met maintenant `quote_type` au moment de créer le token au lieu d'ajouter un préfixe à la chaîne.
- `token_2_find_type.c` utilise désormais `t_token->quote_type` pour décider si on doit désactiver l'expansion ; plus de `ft_strnstr("__SINGLE_QUOTE__")` ni de `+16`.

Fichiers touchés
----------------
- atom.h
- src/init.c
- src/tokenizer_1/token_utils.c
- src/tokenizer_1/quote_gestion.c
- src/parsing_2/tokenizer_2/token_2_find_type.c
- docs/quote_management_plan.md (historique ajouté)

Pourquoi c'est mieux
-------------------
- Plus lisible : l'intention est explicite (champ dédié).
- Plus robuste : on évite les manipulations de chaînes fragiles.
- Plus extensible : on peut ajouter d'autres états (échappement, heredoc, etc.).
- Moins de risques d'effets de bord sur la valeur réelle du token.

Comment valider localement (rapide)
-----------------------------------
1) Rebuild :

```bash
make
```

2) Tests interactifs (quelques cas rapides) :

```bash
# simple quotes (pas d'expansion)
echo "echo 'hello world'" | ./minishell

# double quotes (expansion)
echo "echo \"hello $USER\"" | ./minishell

# nested
printf '%s\n' 'echo "He said '\''hi'\''"' | ./minishell
```

Si tu veux un rendu parfaitement identique à bash pour validation, lance les mêmes commandes dans bash et compare.

Comment revenir en arrière (rollback rapide)
--------------------------------------------
Si besoin urgent : revert la branche git (exemple) :

```bash
git checkout -b backup-before-quote-change
# si tu as commité les changements dans une branche, fais :
# git checkout main && git revert <commit_sha>
```

Points à vérifier après merge
---------------------------
- Lancer la suite `minishell_tester/` et vérifier qu'il n'y a pas de régressions.
- Cas limites : heredoc avec quotes, combinaisons d'échappements profonds, et scripts non-interactifs.

Prochaine étape recommandée
--------------------------
- Ouvrir une MR avec ce changelog et le doc `docs/quote_management_plan.md` mis à jour.
- Ajouter 3 tests automatisés dans `minishell_tester/` couvrant : simple quote, double quote + expansion, nested quotes.

Contact
-------
Si besoin, je peux écrire la MR description complète et les commandes CI.
