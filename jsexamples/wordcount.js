function countWords(str){
if (str.length == 0) return 0;
if (str == null) return 0;
try {
var i = str.match(/\S+/g).length;
    }
catch (err)
  { return 0;}
if (i !== null) return i;
}