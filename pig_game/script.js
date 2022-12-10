'use strict';
function resetPage(){

    scoreOneEl.textContent = 0;
    scoreTwoEl.textContent = 0;
    diceRoll.classList.add('hidden');
}

const playerZero = document.querySelector('.player--0');
const playerOne = document.querySelector('.player--1');
const diceRoll = document.querySelector('.dice');
const btnNew = document.querySelector('.btn--new');
const btnRoll = document.querySelector('.btn--roll');
const btnHold = document.querySelector('.btn--hold');
const scoreOneEl= document.querySelector('#score--0');
const scoreTwoEl = document.getElementById('score--1');
const curr0El = document.getElementById('current--0');
const curr1El = document.getElementById('current--1');


const scores = [0, 0];
let currScore = 0;
let activePlayer = 0;
//two different methods to gain elemnt by id- one is more faster

//set initial values 
resetPage();

btnRoll.addEventListener('click', function(){
    //1.generate new dice on the screen 
    const diceRand = Math.trunc(Math.random() * 6) + 1;
    diceRoll.classList.remove('hidden');
    //manipulating html attribute in js 
    //change to template literal
    diceRoll.src = 'dice-' + diceRand+'.png';
    //2. check if had the value of 1 , if true switch player
    if (diceRand !== 1){
        currScore += diceRand;
        //choosing player dynamically
        document.getElementById('current--' + activePlayer).textContent = currScore;
        
    } else {
        document.getElementById('current--' + activePlayer).textContent = 0;
        activePlayer = activePlayer === 0 ? 1 : 0;
        currScore = 0;
        //toggle does the decision for me 
        //toggling will ensure that the correct user is lighted
        playerZero.classList.toggle('player--active');
        playerOne.classList.toggle('player--active');

    }
});

btnHold.addEventListener('click', function(){
    let highScore = Number(document.getElementById('score--'+ activePlayer).textContent) + currScore;
    currScore = 0;
    document.getElementById('current--' + activePlayer).textContent = 0;
    document.getElementById('score--'+ activePlayer).textContent =highScore;
    
    

    if (highScore < 100){
        playerZero.classList.toggle('player--active');
        playerOne.classList.toggle('player--active');
        
       
        activePlayer = activePlayer === 0 ? 1 : 0;

    }else if (highScore >= 100) {
        document.getElementById('name--' + activePlayer).textContent += 'WINNED!'; 
    }
    
});
