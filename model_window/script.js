'use strict';
const resetPage = function(){
    modal.classList.add('hidden');
    overlay.classList.add('hidden');
}
const openModal = function(){
    console.log('Button clicked');
    modal.classList.remove('hidden');
    overlay.classList.remove('hidden');
};

const modal = document.querySelector('.modal');
const overlay = document.querySelector('.overlay');
const btnCloseModal = document.querySelector('.close-modal');
const btnsOpenModal = document.querySelectorAll('.show-modal');

for (let i = 0 ; i < btnsOpenModal.length; ++i){
    btnsOpenModal[i].addEventListener('click', openModal);
}

btnCloseModal.addEventListener('click', resetPage);

overlay.addEventListener('click', resetPage);

document.addEventListener('keydown',function(e){
    if (e.key === "Escape" && !modal.classList.contains('hidden')){
            resetPage();
        }
});
