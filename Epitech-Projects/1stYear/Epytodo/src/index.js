/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** index.js
*/

const express = require('express');
const app = express();
require('dotenv').config();

// Connect to database
require('./config/db');

// Middleware
app.use(express.json());

// Routes
app.use('/', require('./routes/auth/auth'));
app.use('/', require('./routes/user/user'));
app.use('/', require('./routes/todos/todos'));

// 404 middleware
app.use(require('./middleware/notFound'));

// Start server
const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
});
