# myTeams

## Compilation

```bash
make              # compile l'entièretée du projet
make server       # compile uniquement le binaire du server
make client       # compile uniquement le binaire du client
```

## Lancement

```bash
export LD_LIBRARY_PATH="$(realpath libs/myteams)"
./myteams_server {port} # lance le server (port = port sur lequel le server est disponible)
```
```bash
# sur un autre terminal ou une autre machine
export LD_LIBRARY_PATH="$(realpath libs/myteams)"
./myteams_cli "{interface}" {port} # lance le server (interface = 127.0.0.1 si le server est lancé sur la même machine, sinon l'ip de la machine qui lance le server)
```



## Commandes

- **/help** - *affiche les commandes disponibles.*
- **/login "user_name"** - *créer un compte si l'utilisateur n'existe pas, sinon se connecte.*
- **/logout** - *déconnecte le client.*
- **/users** - *affiche tous les utilisateurs.*
- **/user "user_uuid"** - *affiche les informations de l'utilisateur spécifié.*
- **/send "user_uuid"** "message_body" - *envoie un message privé à l'utilisateur spécifié.*
- **/messages "user_uuid"** - *affiche les messages échangé avec l'utilisateur spécifié.*
- **/subscribe "team_uuid"** - *s'abonne à la team spécifié (l'utilisateur recevera maintenant les messages posté sur cette team).*
- **/subscribed ["team_uuid"]** - *affiche les teams suivie ou affiche les utilisateurs qui suivent la team spécifié.*
- **/unsubscribe "team_uuid"** - *se désabonne de la team spécifié (l'utilisateur ne recevera plus les messages posté sur cette team).*
- **/use ["team_uuid" ["channel_uuid" ["thread_uuid"]]]** - *met le context des commandes sur team/channel/thread.*
- **/create** - *crée une nouvelle team/channel/thread (selon le context).*
- **/list** - *liste les team/channel/thread (selon le context).*
- **/info** - *affiche les infos de la team/channel/thread (selon le context).*
