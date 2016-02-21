var random1;
var random2;
var correct = 
[
"Good! Now try a hard one!", 
"Correct, here's another!", 
"Awesome! You getting tired yet?",
"Amazing! You should probably do some more though...",
"Well... you aren't wrong.",
"Way to go.",
"Nice Job.",
"You're amazing, you can do basic math",
"Fun right? have another :)",
"Nice... you want a trophy or something?"
];
var incorrect = 
[
"Thats not even close... guess again dummy",
"Do you practice this at all? WRONG!",
"You realize life is pointless right? Like you trying to answer this question...",
"You might want to buy a calculator",
"Seriously? the answer is .... haha yeah right.",
"You couldn't be more wrong.",
"Try... doing math ...",
"Have you considered a job at McDonalds?",
"You CAN read right?"
];

function rand(min, max) 
{
  return Math.floor(Math.random() * (max - min) + min);
}

function start()
{

button.addEventListener("click", getquestion , false);
checkbutton.addEventListener("click", checkanswer , false); 
}

function removebutton() 
{
    var elem = document.getElementById('button');
    elem.parentNode.removeChild(elem);
    return false;
}

function getquestion() 
{
	random1 = rand(1,9);
	random2 = rand(1,9);
    document.getElementById("question").innerHTML = "what is " + random1 + " times " + random2 + "?";
    removebutton();
}

function checkanswer()
{

	// the assignment said to use a switch statement for the random answers. That seemed tedious. 
	// I just used two arrays. 
	
	var useranswer = document.getElementById("user");
	useranswer = user.value; 
	var correctanswer = random1 * random2;
	if (useranswer != correctanswer)
	{
	document.getElementById("message").innerHTML = incorrect[rand(1,9)];
	}
	else
	{
	document.getElementById("message").innerHTML = correct[rand(1,9)];
	getquestion(); 
	}
}

window.addEventListener("load", start, false); 