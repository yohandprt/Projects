## COMMAND

    /help <CRLF>                                                                         : Show available commands
    /login <SP> ["user_name"] <CRLF>                                                     : Set the username used by client
    /logout <CRLF>                                                                       : Disconnect the client from the server

    /users <CRLF>                                                                        : Get the list of all users on the domain
    /user <SP> ["user_uuid"] <CRLF>                                                      : Get details about a specific user

    /send <SP> ["user_uuid"] <SP> ["message_body"] <CRLF>                                : Send a message to a specific user
    /messages <SP> ["user_uuid"] <CRLF>                                                  : List all messages exchanged with a user

    /subscribe <SP> ["team_uuid"] <CRLF>                                                 : Subscribe to a team and all its sub-resources
    /subscribed [<SP> ["team_uuid"]] <CRLF>                                              : List subscribed teams, or list subscribers of a team
    /unsubscribe <SP> ["team_uuid"] <CRLF>                                               : Unsubscribe from a team

    /use [<SP> ["team_uuid"] [<SP> ["channel_uuid"] [<SP> ["thread_uuid"]]]] <CRLF>      : Set context to a team / channel / thread

    /create <CRLF>                                                                       : Create a sub-resource based on context (see below)
    /list <CRLF>                                                                         : List sub-resources based on context (see below)
    /info <CRLF>                                                                         : Display current resource details based on context (see below)


## CONTEXT-DEPENDENT COMMANDS

    /create
        No context :
            /create <SP> ["team_name"] <SP> ["team_description"] <CRLF>         : Create a new team
        Team context :
            /create <SP> ["channel_name"] <SP> ["channel_description"] <CRLF>   : Create a new channel
        Team, Channel context :
            /create <SP> ["thread_title"] <SP> ["thread_message"] <CRLF>        : Create a new thread
        Team, Channel, Thread context :
            /create <SP> ["comment_body"] <CRLF>                                : Create a new reply

    /list
        No context:
            /list <CRLF>                : List all existing teams
        Team context:
            /list <CRLF>                : List all existing channels in the team
        Team, Channel context:
            /list <CRLF>                : List all existing threads in the channel
        Team, Channel, Thread context:
            /list <CRLF>                : List all existing replies in the thread

    /info
        No context:
            /info <CRLF>                : Display currently logged-in user details
        Team context:
            /info <CRLF>                : Display currently selected team details
        Team, Channel context:
            /info <CRLF>                : Display currently selected channel details
        Team, Channel, Thread context:
            /info <CRLF>                : Display currently selected thread details


Command-Reply Sequences

>The server reply is defined to contain the 3-digit code, followed by Space <SP>, followed by one line of text, and terminated by the Telnet end-of-line code <CRLF>.

## EXAMPLE

    -> /login <SP> "name" <CRLF>
    <- 800 <SP> User logged in. <CRLF>

    -> /logout <CRLF>
    <- 821 <SP> Service closing connection. <CRLF>

    -> : Request command from client to server
    <- : Reply from server to client

## EXPLANATION OF RETURN CODES BY COMMANDS

    Connection
        <- 820   Service ready for new user.

    Login / Logout
        /login ->
            <- 700 User logged in.
                <- 600 Bad request. missing argument.
                <- 701 User is already logged in.
            <- xxx
        /logout ->
            <- 821 Service closing connection.
                <- 601 Unauthorized. User not logged in.
            <- xxx

    User commands
        /users ->
            <- 800 Command okay.
                <- 601 Unauthorized. User not logged in.
            <- xxx
        /user ->
            <- 800 Command okay.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
            <- xxx

    Messaging
        /send ->
            <- 800 Command okay.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
            <- xxx
        /messages ->
            <- 800 Command okay.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
            <- xxx

    Subscription
        /subscribe ->
            <- 800 Command okay.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
                <- 609 Conflict. Resource already exists.
            <- xxx
        /subscribed ->
            <- 800 Command okay.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
            <- xxx
        /unsubscribe ->
            <- 800 Command okay.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
                <- 609 Conflict. Resource already exists.
            <- xxx

    Context
        /use ->
            <- 800 Command okay.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
            <- xxx

    Context-dependent commands
        /create ->
            <- 801 Resource created successfully.
                <- 600 Bad request. missing argument.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
                <- 609 Conflict. Resource already exists.
            <- xxx
        /list ->
            <- 800 Command okay.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
            <- xxx
        /info ->
            <- 800 Command okay.
                <- 601 Unauthorized. User not logged in.
                <- 604 Not found. The requested resource does not exist.
            <- xxx

    Informational
        /help ->
            <- 814 Help message listing available commands.
            <- xxx


## NUMERIC ORDER LIST OF REPLY CODES

    600 Bad request. missing argument.
    601 Unauthorized. User not logged in.
    604 Not found. The requested resource does not exist.
    609 Conflict. Resource already exists.
    650 Unknown command.

    700 User logged in.
    701 User is already logged in.

    800 Command okay.
    801 Resource created successfully.
    814 Help message listing available commands.
    820 Service ready for new user.
    821 Service closing connection.