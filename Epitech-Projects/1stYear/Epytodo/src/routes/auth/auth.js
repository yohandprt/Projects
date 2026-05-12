/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** auth.js
*/

const express = require('express');
const router = express.Router();
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const db = require('../../config/db');
require('dotenv').config();

// Register a new user

router.get("/debug", async (req, res) => {
    const all_users = await db.promise().query("SELECT * FROM user");
    const all_todos = await db.promise().query("SELECT * FROM todo");
    const describe_user = await db.promise().query("DESCRIBE user");
    const describe_todo = await db.promise().query("DESCRIBE todo");

    const return_json = {"users": all_users[0], "todos": all_todos[0], "desc_user": describe_user[0], "desc_todo": describe_todo[0]};
    return res.status(200).json(return_json);
});

router.post('/register', async (req, res) => {
    const { email, name, firstname, password } = req.body;
    
    if (!email || !name || !firstname || !password) {
        return res.status(400).json({ msg: "Bad parameter" });
    }

    try {
        // Check if user already exists
        db.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
            if (err) {
                return res.status(500).json({ msg: "Internal server error" });
            }
            if (results.length > 0) {
                return res.status(400).json({ msg: "Account already exists" });
            }

            // Hash password
            const hashedPassword = await bcrypt.hash(password, 10);

            // Insert new user
            db.query('INSERT INTO user (email, name, firstname, password) VALUES (?, ?, ?, ?)', 
                [email, name, firstname, hashedPassword], (err, results) => {
                    if (err) {
                        return res.status(500).json({ msg: "Internal server error" });
                    }

                    // Create JWT token
                    const token = jwt.sign({ id: results.insertId }, process.env.SECRET);
                    res.json({ token });
                });
        });
    } catch (err) {
        res.status(500).json({ msg: "Internal server error" });
    }
});

// Login user
router.post('/login', (req, res) => {
    const { email, password } = req.body;
    
    if (!email || !password) {
        return res.status(400).json({ msg: "Bad parameter" });
    }

    try {
        db.query('SELECT * FROM user WHERE email = ?', [email], async (err, results) => {
            if (err) {
                return res.status(500).json({ msg: "Internal server error" });
            }
            if (results.length === 0) {
                return res.status(401).json({ msg: "Invalid Credentials" });
            }

            const user = results[0];
            const isMatch = await bcrypt.compare(password, user.password);
            
            if (!isMatch) {
                return res.status(401).json({ msg: "Invalid Credentials" });
            }

            // Create JWT token
            const token = jwt.sign({ id: user.id }, process.env.SECRET);
            res.json({ token });
        });
    } catch (err) {
        res.status(500).json({ msg: "Internal server error" });
    }
});

module.exports = router;
