// import 
import { form, input, list } from './config.js';
const todo = require('../../src/routes/todos/todos.query');

// gestion du formulaire : lorsqu'on clique sur "Ajouter"
form.addEventListener("submit", function(e) {
    e.preventDefault(); // empêche le rechargement de la page
    const text = input.value.trim(); // récup le texte sans espace inutile

    if (text !== '') { // si le champ n'est pas vide
        addTodo(text); // ajoute la tâche
        todo.addTodo({ title: text, description: '', due_time: '', user_id: 1, status: 'not started' });
        input.value = ''; // réinitialise le champ
    }
});

// fonction pour créer une nouvelle tâche
function addTodo(text) {
    const li = document.createElement("li"); // crée une balise <li>

    // ajoute du HTML dans la balise <li> : texte + bouton suppression
    li.innerHTML = `
    <span>${text}</span>
    <button aria-label="Supprimer cette tâche">&times;</button>
    `;
    // clique sur le texte => barre la tâche
    li.querySelector("span").addEventListener("click", () => {
        li.classList.toggle("done"); // ajoute ou retire la classe "done"
    });

    // clique sur la croix => supprime la tâche
    li.querySelector("button").addEventListener("click", () => {
        li.remove(); // retire l'élément de la liste
    });

    list.appendChild(li); // ajoute la balise <li> dans la liste
}