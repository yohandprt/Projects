/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** todos.js
*/

const express = require('express');
const router = express.Router();
const auth = require('../../middleware/auth');
const { getAllTodos, getTodoById, createTodo, updateTodo, deleteTodo } = require('./todos.query');

// Get all todos
router.get('/todos', auth, async (req, res) => {
    await getAllTodos(req, res);
});

// Get todo by ID
router.get('/todos/:id', auth, async (req, res) => {
    await getTodoById(req, res);
});

// Create todo
router.post('/todos', auth, async (req, res) => {
    await createTodo(req, res);
});

// Update todo
router.put('/todos/:id', auth, async (req, res) => {
    await updateTodo(req, res);
});

// Delete todo
router.delete('/todos/:id', auth, async (req, res) => {
    await deleteTodo(req, res);
});

module.exports = router;
