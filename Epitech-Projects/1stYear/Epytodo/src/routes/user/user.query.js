/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** user.query.js
*/

const db = require('../../config/db');
const bcrypt = require('bcryptjs');
require('dotenv').config();

const updateUser = async (req, res) => {
    const {email, name, firstname, password} = req.body;
    const id = req.params.id;

    try {
        const hashed_pass = await bcrypt.hash(password, 10);
        await db.promise().query("UPDATE user SET email=?, password=?, name=?, firstname=? WHERE id=?",
            [email, hashed_pass, name, firstname, id]);
        const [user] = await db.promise().query('SELECT * FROM user WHERE id = ?', [id]);
        res.status(200).json(user[0]);
        return user[0];
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const deleteUser = async (req, res) => {
    try {
        const id = req.params.id;
        await db.promise().query("DELETE FROM user WHERE id=?", [id]);
        res.status(200).json({msg: `Successfully deleted record number: ${id}`});
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const getUserTodos = async (req, res) => {
    const user_id = req.user.id;

    try {
        const [all_todos] = await db.promise().query("SELECT * FROM todo WHERE user_id=?", [user_id])
        res.status(200).json(all_todos);
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const getUserByIdentifier = async (req, res) => {
    const identifier = req.params.identifier;
    let user;

    try {
        if (isNaN(identifier)) {
            [user] = await db.promise().query("SELECT * FROM user WHERE email=?", [identifier]);
        } else {
            [user] = await db.promise().query("SELECT * FROM user WHERE id=?", [identifier]);
        }
        if (user.length === 0) {
            return res.status(404).json({msg: "Not found"});
        } else {
            res.status(200).json(user[0]);
        }
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const getUserByEmail = async (req, res) => {
    const email = req.user.email;

    try {
        const [user] = await db.promise().query("SELECT * FROM user WHERE email=?", [email]);
        if (user.length === 0) {
            return res.status(404).json({msg: "Not found"});
        } else {
            res.status(200).json(user[0]);
        }
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

const getUserById = async (req, res) => {
    const id = req.user.id;

    try {
        const [user] = await db.promise().query("SELECT * FROM user WHERE id=?", [id]);
        if (user.length === 0) {
            return res.status(404).json({msg: "Not found"});
        } else {
            res.status(200).json(user[0]);
        }
    } catch {
        res.status(500).json({msg: "Internal server error"});
    }
};

module.exports = {
    updateUser,
    deleteUser,
    getUserTodos,
    getUserByIdentifier,
    getUserByEmail,
    getUserById
};
