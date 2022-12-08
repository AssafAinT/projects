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
//event listener 
// document.querySelector('.guess').value = Math.random() % 100;
const secretNumber = Math.trunc(Math.random() * 20) + 1;
let currScore = Number(document.querySelector('.score').textContent);
document.querySelector('.number').textContent = secretNumber;
document.querySelector('.check').addEventListener('click',function(){
    const guess = Number(document.querySelector('.guess').value);
    console.log(guess);

    //indicating user that he hasnt clicked any number
    if (!guess) {
        document.querySelector('.message').textContent = 'No number pressed try again';
    }
    //when player wins 
    else if(guess === secretNumber){
        document.querySelector('.message').textContent = 'Correct Numer! 🥳';

        document.querySelector('body').style.backgroundColor = '#60b347';
        document.querySelector('.number').style.width = '30rem';
    }
    //when guess too low
    else if (guess < secretNumber){
        if (currScore > 1){

            document.querySelector('.message').textContent = 'Too Low 🫣';
            document.querySelector('.score').textContent = --currScore;
        } else {
            document.querySelector('.message').textContent = 'Game Over 🫣';
            document.querySelector('.score').textContent = --currScore;
        }
    }
    //when guess too high
    else if (guess > secretNumber){
        if (currScore > 1){
        document.querySelector('.message').textContent = 'Too High 🫣';
        document.querySelector('.score').textContent = --currScore;
        }
        else {
            document.querySelector('.message').textContent = 'Game Over 🫣';
            document.querySelector('.score').textContent = --currScore;
        }

    }

})



