// Create a "close" button and append it to each list item
let appendCloseButton = function(){
    let span = document.createElement("SPAN");
    let txt = document.createTextNode("\u00D7");
    span.className = "close";
    span.appendChild(txt);
    return span;
}
let createDate = function(){
    const date = new Date();
    let day = date.getDate();
    let month = date.getMonth() + 1;
    let year = date.getFullYear();
    let currentDate = document.createTextNode(`${day}-${month}-${year} | `);
    return currentDate;
}

let myNodelist = document.getElementsByTagName("LI");
for (let i = 0; i < myNodelist.length; i++) {
    myNodelist[i].innerHTML = createDate().nodeValue + " " + myNodelist[i].innerHTML;
    myNodelist[i].appendChild(appendCloseButton());  
}

// Click on a close button to hide the current list item
let close = document.getElementsByClassName("close");
for (let i = 0; i < close.length; i++) {
  close[i].onclick = function () {
    let div = this.parentElement;
    div.style.display = "none";
  };
}

// Add a "checked" symbol when clicking on a list item
let list = document.querySelector("ul");
list.addEventListener(
  "click",
  function (ev) {
    if (ev.target.tagName === "LI") {
      ev.target.classList.toggle("checked");
    }
  },
  false
);

// Create a new list item when clicking on the "Add" button
function newElement() {
    
    let li = document.createElement("li");
    let inputValue = document.getElementById("todoInput").value;
    let t = document.createTextNode(inputValue);
    li.appendChild(createDate());
    li.appendChild(t);
    if (inputValue === '') {
      alert("You must write something!");
    } else {
      document.getElementById("myUL").appendChild(li);
    }
    document.getElementById("todoInput").value = "";
  
    li.appendChild(appendCloseButton());
  
    for (i = 0; i < close.length; i++) {
      close[i].onclick = function() {
        let div = this.parentElement;
        div.style.display = "none";
      }
    }
  }

const AddButton = document.getElementById("todoInput");
AddButton.addEventListener('keydown',function(e){
    if (e.key === "Enter"){
            newElement();
        }
});
function sortList(){
    const listArray = [];

    for (let i = 0; i < myNodelist.length; ++i) {
        listArray.push(myNodelist[i].innerHTML);
    }
    //need to improve sort algorithm
    listArray.sort();
    for (let i = 0; i < myNodelist.length; ++i) {
        myNodelist[i].innerHTML = listArray[i];
    }
}

function clearList(){
    let listRunner = document.querySelector('#myUL');

    for (let i = 0; i < listRunner.children.length; ++i){
        listRunner.removeChild(listRunner.childNodes[i]);
    }

}

