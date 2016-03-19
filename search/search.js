// Your use of the YouTube API must comply with the Terms of Service:
// https://developers.google.com/youtube/terms

function RandomWord() 
    {
        var requestStr = "http://randomword.setgetgo.com/get.php";

        $.ajax({
            type: "GET",
            
            url: requestStr,
            dataType: "jsonp",
            jsonpCallback: 'search'
        });
    }
    
// Helper function to display JavaScript value on HTML page.

var randomid = '';
function showResponse(response) {
	randomid = '';
    var responseString = JSON.stringify(response, '', 2);
    string = responseString;
    var n = string.indexOf("videoId");
    for (var i=11; i < 22 ; i++)
    {
    randomid += string[n+i]
    }
    if (randomid[0] == ":")
    	{
    	RandomWord();
    	}
    else
    {
    player.loadVideoById(randomid);
    }
}

// Called automatically when JavaScript client library is loaded.
function onClientLoad() {
    gapi.client.load('youtube', 'v3', onYouTubeApiLoad);
}

// Called automatically when YouTube API interface is loaded (see line 9).
function onYouTubeApiLoad() {
    // This API key is intended for use only in this lesson.
    // See https://goo.gl/PdPA1 to get a key for your own applications.
    gapi.client.setApiKey('AIzaSyBwZOpcHtNfvtI0uzEYmcnrqyurX3Hiof8');

    RandomWord();
}



function search(data) {
    // Use the JavaScript client library to create a search.list() API call.
    
    term = data.Word;
    document.getElementById("string").innerHTML = term;
    
    var request = gapi.client.youtube.search.list({
        part: 'snippet',
        q: term

    });
    
    // Send the request to the API server,
    // and invoke onSearchRepsonse() with the response.
    request.execute(onSearchResponse);
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
          events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange
          }
        });
      }

      // 4. The API will call this function when the video player is ready.
      function onPlayerReady(event) {
                 
            	
            	
                
            
      }

     
      function onPlayerStateChange(event) {
      if(event.data === 0) //state 0 is when a video ends
            {          
            	
            	RandomWord();
                
            }
      
      }
      
   
      
      
      


        
