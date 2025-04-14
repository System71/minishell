// EXEMPLE REGROUPEMENT
typedef struct s_redirection{
	int type; // Par exemple, T_REDIRECT_IN, T_REDIRECT_OUT, T_APPEND, T_HEREDOC 
	char *target; // Le fichier ou le délimiteur 
	struct s_redirection *next;
} t_redirection;

typedef struct s_command {
	char **args; // Tableau dynamique ou liste chaînée des arguments
	t_redirection *redirs; // Liste des redirections associées
	struct s_command *next; // Pour chaîner les commandes d'un pipeline
} t_command;

// HERE_DOC
int heredoc_handle(t_token *tokens);

// EXPAND
char *check_expand(const char *input, t_quote_type quote);
void expand_handle(t_token *tokens);

────────────────────────────── 3. Gestion du Heredoc
Le résultat (le contenu complet du heredoc) sera alors stocké dans le token,
sous forme de chaîne de caractères, au lieu de conserver le signe << et le délimiteur séparément.
• Gestion asynchrone :

Certains choisissent de gérer le heredoc après le regroupement dans une phase dédiée,
ce qui permet de séparer la lecture interactive de l’opérateur et son traitement.

Il faut cependant veiller à ce que cette lecture soit gérée proprement au niveau des signaux
(Ctrl-C, par exemple) pour respecter le comportement de bash.

────────────────────────────── 4. Gestion de l'Expand
Cette étape consiste à remplacer les occurrences de $VAR par leur valeur. Quelques points importants :
• Ordre d'exécution : Il est souvent préférable de faire l’expansion après avoir regroupé
les tokens afin d’avoir une vision claire de chaque argument et de ses segments.
• Contexte des quotes :
Dans les quotes simples, l'expansion ne doit pas se faire.
Dans les quotes doubles, seuls certains caractères (comme $ pour les variables et éventuellement )
doivent être traités différemment.
• Cas particuliers : Pense à gérer le cas de $? qui renvoie le status de la dernière commande,
ainsi que d’autres variables éventuellement présentes dans l'environnement.

────────────────────────────── 5. Parser Final
Le parser doit transformer la liste de tokens déjà regroupés en une structure de commande exploitable lors de l'exécution.
• Création de structures de commandes :
Crée une structure (par exemple t_command) qui comprendra le tableau des arguments (la commande et ses paramètres),
les redirections et un pointeur vers la commande suivante dans le cas d’un pipeline.
• Association des redirections :

Lorsqu’un token de redirection est rencontré, associe-le directement à la commande en cours,
en stockant notamment le type de redirection et sa cible.
• Validation syntaxique :

Assure-toi de vérifier la présence d’un token cible après chaque opérateur de redirection et
renvoie une erreur syntaxique s’il manque un élément essentiel.
• Liaison avec l'exécution :

Le parser final doit produire une liste de noeuds de commande prête à être envoyée à l'exécuteur
qui se chargera de gérer les forks, pipes, et redirections d’entrée/sortie.

/*initialiser une liste de commandes vide  */
/*créer une nouvelle commande courante*/
/**/
/*pour chaque token dans la liste :*/
/*    si token est un pipe (T_PIPE) :*/
/*        terminer la commande courante, ajouter à la liste*/
/*        créer une nouvelle commande courante  */
/*    sinon si token est une redirection (T_REDIRECT_IN, T_REDIRECT_OUT, T_APPEND, T_HEREDOC) :*/
/*        vérifier que le token suivant existe (il doit représenter la cible)  */
/*        associer ce token et son suivant à la structure de redirection de la commande courante  */
/*        (pense à avancer l’index pour sauter le token utilisé comme cible)  */
/*    sinon (donc token de type T_WORD) :*/
/*        ajouter le contenu (en fusionnant éventuellement ses segments) à la liste d’arguments de la commande courante*/
/**/
/*ajouter la dernière commande à la liste (si non vide)*/

/*Gestion des erreurs :*/
/*Si une redirection est présente sans token associé pour la cible (fichier ou délimiteur), il faut générer une erreur syntaxique similaire à bash.*/
/**/
/*Fusion des tokens successifs :*/
/*Parfois, des tokens T_WORD consécutifs pourraient être fusionnés, notamment s’ils résultent d’un découpage trop fin dans le lexer. */
/*Fais attention à bien distinguer un cas où l’espace est significatif (séparation d’arguments) ou non.*/

