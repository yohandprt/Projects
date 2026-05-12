/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** user.js
*/

const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const auth = require('../../middleware/auth');
const { getUserByIdentifier, getUserById, getUserByEmail, getUserTodos, updateUser, deleteUser } = require('./user.query');

// Get current user info
router.get('/user', auth, async (req, res) => {
    req.params.id = req.user.id;
    await getUserById(req, res);
});

// Get user todos
router.get('/user/todos', auth, async (req, res) => {
    getUserTodos(req, res);
});

// Get user by id or email
router.get('/users/:identifier', auth, async (req, res) => {
    await getUserByIdentifier(req, res);
});

// Update user
router.put('/users/:id', auth, async (req, res) => {
    await updateUser(req, res);
});

// Delete user
router.delete('/users/:id', auth, async (req, res) => {
    await deleteUser(req, res);
});

module.exports = router;
