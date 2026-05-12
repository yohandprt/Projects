# EpyTodo

EpyTodo is a RESTful API built with Node.js and MySQL, designed to manage tasks for different users. It provides features for user registration, authentication, user management, and task management.

## Technologies Used

- Node.js
- Express
- MySQL
- JWT (jsonwebtoken)
- bcryptjs
- dotenv
- mysql2

## Project Structure

```bash
.
├── .env
├── package.json
├── epytodo.sql
└── src
    ├── config
    │   └── db.js
    ├── index.js
    ├── middleware
    │   ├── auth.js
    │   └── notFound.js
    └── routes
        ├── auth
        │   └── auth.js
        ├── todos
        │   ├── todos.js
        │   └── todos.query.js
        └── user
            ├── user.js
            └── user.query.js
```


## Configuration

Create a `.env` file at the root of the project with the following variables:

```env
MYSQL_DATABASE=epytodo
MYSQL_HOST=localhost
MYSQL_USER=root
MYSQL_ROOT_PASSWORD=yourpassword
PORT=3000
SECRET=your_jwt_secret
```

## Database

The `epytodo.sql` file contains the database schema, with two tables:

- user

- todo

You can import it with the following command:

```bash
cat epytodo.sql | mysql -u root -p
```

## Authentication

Protected routes require a JSON Web Token (JWT) in the Authorization header. Tokens can be obtained via the `/register` or `/login` routes.
## Auth Routes
| Method |	Route | Description
|:------- |:-----:| ----------:|
 POST | /register | Register a new user
 POST | /login | Log in a user
## User Routes
| Method | Route | Description
|:------- |:-----:| ----------:|
GET	| /user	| Get current user information
GET	| /user/todos	| Get current user's todos
GET	| /users/:id/email |	Get user information by ID/email
PUT |	/users/:id	| Update a user
DELETE |	/users/:id	| Delete a user
## Todo Routes
| Method |	Route |	Description
|:------- |:-----:| ----------:|
GET |	/todos |	Get all todos
GET	| /todos/:id |	Get a specific todo
POST |	/todos	| Create a new todo
PUT	| /todos/:id |	Update a todo
DELETE |	/todos/:id |	Delete a todo
## Running the Project
## Installation

```bash
npm install
```

## Start

```bash
npm start
```

The server will be available at: http://localhost:3000.
## Best Practices

- Follow the recommended project architecture

- Use middleware for authentication and error handling

- Securely hash passwords

- Handle errors consistently with clear messages and proper HTTP codes

## Notes

- The `node_modules` folder must be ignored using `.gitignore`

- No data should be inserted in the `epytodo.sql` file

- All API responses are in JSON format

## Authors
- [@llosts](https://github.com/llosts)
- [@yohandprt](https://github.com/yohandprt)
- [@Alexandre2806](https://github.com/Alexandre2806)