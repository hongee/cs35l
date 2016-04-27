function map(collection, func) {
  var retCollection = collection;
  for(var i = 0; i < collection.length; i++) {
    retCollection[i] = func(collection[i]);
  }
  return retCollection;
}

function pow(num) {
  return (function(i) {
    var r = i;
    for(var j=0; j<num; j++) {
      r *= i;
    }
    return r;
  });
}

var pow3 = pow(3);

var arr = [1,2,3,4,5];
var newarr = map(arr, pow3);
console.log(newarr);
