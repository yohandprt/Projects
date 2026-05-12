/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** todos.query.js
*/

const db = require('../../config/db');

const createTodo = async (req, res) => {
    const {title, description, due_time, user_id, status} = req.body;

    if (!title || !description || !due_time || !user_id || !status) {
        return res.status(400).json({ msg: 'Bad parameter' });
    }
    try{
        const [result] = await db.promise().query("INSERT INTO todo (title, description, due_time, user_id, status) VALUES (?, ?, ?, ?, ?)",
        [title, description, due_time, user_id, status]);
        const [added] = await db.promise().query("SELECT * FROM todo WHERE id = ?", [result.insertId]);
        res.status(200).json(added[0]);
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const updateTodo = async (req, res) => {
    const {title, description, due_time, user_id, status} = req.body;
    const id = req.params.id;

    try {
        await db.promise().query("UPDATE todo SET title=?, description=?, due_time=?, user_id=?, status=? WHERE id=?",
        [title, description, due_time, user_id, status, id]);
        const [updated] = await db.promise().query("SELECT * FROM todo WHERE id = ?", [id]);
        res.status(200).json(updated[0]);
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const deleteTodo = async (req, res) => {
    const id = req.params.id;

    try {
        await db.promise().query("DELETE FROM todo WHERE id=?", [id]);
        res.status(200).json({msg: `Successfully deleted record number: ${id}`});
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const getAllTodos = async (req, res) => {
    try {
        const [all_todos] = await db.promise().query("SELECT * FROM todo");
        res.status(200).json(all_todos);
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const getTodoById = async (req, res) => {
    const id = req.params.id;

    try {
        const [todo] = await db.promise().query("SELECT * FROM todo WHERE id=?", [id]);
        if (todo.length === 0) {
            return res.status(404).json({msg: "Not found"});
        } else {
            res.status(200).json(todo[0]);
        }
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

module.exports = {
    createTodo,
    updateTodo,
    deleteTodo,
    getAllTodos,
    getTodoById
};
