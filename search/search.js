// 2016 John Madison 
// johnmadison.github.io
// IF YOU STEAL THIS WITHOUT PERMISSION 
// I WILL COME TO YOUR HOUSE
// AND EAT THE CONTENTS OF YOUR FRIDGE.
//            AND THEN LEAVE THE DOOR OPEN.

// KK? plz be a good guy and not a bad guy 

// like if you think this is cool maybe you could hire me.

// OR donate some bitcoin to 1M671nZ2niy2SpABtoeX9qCRpnnBGmw8Sb

// This is a GET request to setget.go.com 
// a very cool resource
// after it gets a reponse we jump down to search()
var i = 0;
function RandomWord() 
    {
    document.body.style.backgroundImage = "url('static.gif')";
        var requestStr = "http://randomword.setgetgo.com/get.php";

        $.ajax({
            type: "GET",
            url: requestStr,
            dataType: "jsonp",
            jsonpCallback: 'search'
        });
    }
    
function search(data) {
    // Use the JavaScript client library to create a search.list() API call.
    
    term = data.Word;
    document.getElementById("string").innerHTML = term;
    document.getElementById('string').style.color = '#'+Math.floor(Math.random()*16777215).toString(16);
    
    var request = gapi.client.youtube.search.list({
        part: 'snippet',
        q: term

    });
    

    request.execute(onSearchResponse);
}


var randomid = '';
function showResponse(response) {

// Do some black magic to extract the youtube id from the JSON response

	randomid = '';
    var responseString = JSON.stringify(response, '', 2);
    string = responseString;
    var n = string.indexOf("videoId");
    for (var i=11; i < 22 ; i++)
    {
    randomid += string[n+i]
    }
    
    // If the search comes back with no response 
    // because some words are REALLY that obscure.
    // go ahead and load a new word and video
    
    if (randomid[0] == ":")
    	{
    	RandomWord();
    	}
    else
    {
    player.loadVideoById(randomid);
    }
}


function onClientLoad() {
    gapi.client.load('youtube', 'v3', onYouTubeApiLoad);
}

// GET YOUR OWN YOUTUBE DATA API KEY -- this one is mine....

function onYouTubeApiLoad() {
    // This API key is intended for use only in this lesson.
    // See https://goo.gl/PdPA1 to get a key for your own applications.
    gapi.client.setApiKey('AIzaSyBwZOpcHtNfvtI0uzEYmcnrqyurX3Hiof8');

//start the party 

    RandomWord();
}


// Called automatically with the response of the YouTube API request.

function onSearchResponse(response) {
    showResponse(response);
}

var tag = document.createElement('script');

      tag.src = "https://www.youtube.com/iframe_api";
      var firstScriptTag = document.getElementsByTagName('script')[0];
      firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);

      // 3. This function creates an <iframe> (and YouTube player)
      //    after the API code downloads.
      var player;
      function onYouTubeIframeAPIReady() {
        player = new YT.Player('player', {
          height: '390',
          width: '640',
          videoId: randomid,
          disablekb: 1,
          iv_load_policy: 3,
          modestbranding: 1,
          events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange
          }
        });
      }

      //The API will call this function when the video player is ready.
      function onPlayerReady(event) 
      {
      // this is kinda left over from some older code. 
      // left it cuz im a scared to change it. 
      }

     
      function onPlayerStateChange(event) 
      {
      if(event.data === 0) //state 0 is when a video ends
            {                      	
            	RandomWord();
            }
      if(event.data === 1) 
            {   
            	document.body.style.backgroundImage = "";
            	document.getElementById("count").innerHTML = i;
            	i++;
            }
      
      }
      
   
      
      
      


        
