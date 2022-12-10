'use strict';
function resetPage(){

    scoreOneEl.textContent = 0;
    scoreTwoEl.textContent = 0;
    diceRoll.classList.add('hidden');
}


const diceRoll = document.querySelector('.dice');
const btnNew = document.querySelector('.btn--new');
const btnRoll = document.querySelector('.btn--roll');
const btnHold = document.querySelector('.btn--hold');
const scoreOneEl= document.querySelector('#score--0');
const scoreTwoEl = document.getElementById('score--1');
//two different methods to gain elemnt by id- one is more faster

//set initial values 
resetPage();

btnRoll.addEventListener('click', function(){
    //1.generate new dice on the screen 
    //2. check if had the value of 1 , if true switch player
    const diceRand = Math.trunc(Math.random() * 6) + 1;
    diceRoll.classList.remove('hidden');
    //manipulating html attribute in js 
    //change to template literal
    diceRoll.src = 'dice-' + diceRand+'.png';
});
