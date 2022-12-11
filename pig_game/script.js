'use strict';
function resetPage(){
    // playing = true;
    scoreOneEl.textContent = 0;
    scoreTwoEl.textContent = 0;
    diceRoll.classList.add('hidden');
    playerZero.classList.add('player--active');
}
const switchPlayer = function(){
    document.getElementById('current--' + activePlayer).textContent = 0;
    activePlayer = activePlayer === 0 ? 1 : 0;
    currScore = 0;
    //toggle does the decision for me 
    //toggling will ensure that the correct user is lighted
    playerZero.classList.toggle('player--active');
    playerOne.classList.toggle('player--active');
}

const showWhoOwn = function(){
    document.querySelector(`.player--${activePlayer}`).classList.add('player--winner');
    document.querySelector(`.player--${activePlayer}`).classList.remove('player--active');
    document.getElementById('name--' + activePlayer).textContent += 'WINNED!'; 
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
let playing = true;
//two different methods to gain elemnt by id- one is more faster

//set initial values 
resetPage();
btnRoll.addEventListener('click', function(){
    if (playing) {
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
            
            switchPlayer();
        }
    }
});

btnHold.addEventListener('click', function(){
    if (playing) {

        scores[activePlayer] += currScore; 
        document.getElementById('score--'+ activePlayer).textContent =scores[activePlayer];
        
        if (scores[activePlayer] < 20){
            switchPlayer();
            
        }else if (scores[activePlayer] >= 20) {
            playing = false;
            showWhoOwn();
        }   
    }
});

btnNew.addEventListener('click', function(){
    resetPage();
});
