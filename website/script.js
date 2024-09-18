function toggleMenu() {
    const navLinks = document.getElementById('nav-links');
    navLinks.classList.toggle('show');
}

const element = document.getElementById('devlog_title');
const main = "riseros-";
const texts = ["docs", "devlog"];
let current_text = texts[0];
let text_index = 0;
let index = 0;
let is_adding = true;
let cursor_visible = true;
let delete_index = main.length;

function typeEffect() {
    if (is_adding) {
        element.textContent = main + current_text.slice(0, index) + (cursor_visible ? '|' : '');
        index++;
        
        if (index > current_text.length) {
            is_adding = false;
            setTimeout(typeEffect, 1500);  
            return;
        }
    } else {
        element.textContent = main + current_text.slice(0, index) + (cursor_visible ? '|' : '');
        index--;

        if (index < 0) {
            is_adding = true;
            text_index = (text_index + 1) % texts.length;  
            current_text = texts[text_index];
            index = 0;  
        }
    }

    setTimeout(typeEffect, is_adding ? 100 : 50);
}

typeEffect();

