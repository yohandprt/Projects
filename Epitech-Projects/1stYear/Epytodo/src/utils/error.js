/*
** EPITECH PROJECT, 2024
** B-WEB-200-LIL-2-1-epytodo-yohan.dupret
** File description:
** error.js
*/

// Common error handler
exports.handleServerError = (res, err) => {
  console.error('Server error:', err);
  return res.status(500).json({ "msg": "Internal server error" });
};

// Handle not found
exports.handleNotFound = (res) => {
  return res.status(404).json({ "msg": "Not found" });
};

// Handle bad parameters
exports.handleBadParameter = (res) => {
  return res.status(400).json({ "msg": "Bad parameter" });
};
