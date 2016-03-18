// Your use of the YouTube API must comply with the Terms of Service:
// https://developers.google.com/youtube/terms

    function RandomWord() 
    {
        var requestStr = "http://randomword.setgetgo.com/get.php";

        $.ajax(
        {
            type: "GET",
            url: requestStr,
            dataType: "jsonp",
            jsonpCallback: 'RandomWordComplete'
        }
        );
        return data.Word;
    }

   

// Helper function to display JavaScript value on HTML page.


function showResponse(response) {
    var responseString = JSON.stringify(response, '', 2);
    string = responseString;
    var n = string.indexOf("videoId");
    for (var i=4; i < 15; i++)
    for (var i=11; i < 22 ; i++)
    {
    id += string[n+i]
    }
}

// Called automatically when JavaScript client library is loaded.
function onClientLoad() {
    gapi.client.load('youtube', 'v3', onYouTubeApiLoad);
}

// Called automatically when YouTube API interface is loaded (see line 9).
function onYouTubeApiLoad() {

    gapi.client.setApiKey('AIzaSyBwZOpcHtNfvtI0uzEYmcnrqyurX3Hiof8');

    search();
}

function search() {
    // Use the JavaScript client library to create a search.list() API call.
    term = prompt("search term");
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