/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** notFound.js
*/

const notFound = (req, res, next) => {
    res.status(404).json({ msg: "Not found" });
};

module.exports = notFound;
