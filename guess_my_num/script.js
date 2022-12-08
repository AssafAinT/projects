"use strict";
/*
console.log(document.querySelector('.message').textContent);

//DOM connection point between html and js 
//document is the root of html - entry point
//complete representation of the html
//the DOM is not part of js language the 
//its part of web API'S that can interact with js

//manipulating one of the dom element


//changing DOM number element to first test
document.querySelector('.number').textContent = 13;
document.querySelector('.score').textContent = 10;

document.querySelector('.guess').value = 23;
console.log(document.querySelector('.guess').value);
*/

let secretNumber = Math.trunc(Math.random() * 20) + 1;
let currScore = Number(document.querySelector('.score').textContent);

function handleGuess(string, is_win){
    document.querySelector('.message').textContent = string;
    
}
function adaptScore(){
    document.querySelector('.score').textContent = --currScore;
}
function resetConfig(){
    secretNumber = Math.trunc(Math.random() * 20) + 1;
    currScore = 20;
    document.querySelector('.message').textContent = 'Start guessing...';
    document.querySelector('.score').textContent = currScore;
    document.querySelector('.number').textContent = '?';
    document.querySelector('body').style.backgroundColor = '#222';
    document.querySelector('.number').style.width = '15rem';
}
document.querySelector('.check').addEventListener('click',function(){
    const guess = Number(document.querySelector('.guess').value);
    console.log(guess);
    
    //indicating user that he hasnt clicked any number
    if (!guess) {
        document.querySelector('.message').textContent = 'No number pressed try again';
    }
    //when player wins 
    else if(guess === secretNumber){
        handleGuess('Correct Numer! 🥳');
        
        document.querySelector('body').style.backgroundColor = '#60b347';
        document.querySelector('.number').style.width = '30rem';
    }
    //when guess too low
    else if (guess < secretNumber){
        if (currScore > 1){
            handleGuess('Too Low 🫣');
            adaptScore();
        } else {
            handleGuess('Game Over 🫣');
            adaptScore();
        }
    }
    //when guess too high
    else if (guess > secretNumber){
        if (currScore > 1){
            handleGuess('Too High 🫣');
            adaptScore();
        }
        else {
            handleGuess('Game Over 🫣');
            adaptScore();
        }
        
    }
    
    
});

//once again pressed restoring values 
document.querySelector('.again').addEventListener('click',function(){
    
    resetConfig();
});
