
var cpp;
var MathJaxIsLoaded=false;


MathJax.Hub.Config({
  SVG: {
  }
});

MathJax.Hub.Register.MessageHook("Math Processing Error",function (message) {
    console.log(message)
});

MathJax.Hub.Register.MessageHook("TeX Jax - parse error",function (message) {
    console.log(message)
});

MathJax.Hub.Register.StartupHook("End",function () {

    MathJaxIsLoaded=true;

    if(cpp){
        cpp.MathJaxLoaded();
    }

});

MathJax.Hub.Register.MessageHook('End Update', function (message) {
    
    let svgs = document.getElementsByTagName('svg');    
    let latex= document.getElementById('MathJax-Element-1').innerHTML;
    if(svgs.length==2){
        cpp.MathJaxDone(latex,svgs[0].outerHTML,svgs[1].outerHTML);
    }
    
        
    })

window.UpdateOutput = function (tex) {
    var math = MathJax.Hub.getAllJax("MathOutput")[0];
    MathJax.Hub.queue.Push(["Text", math, tex]);
}

//setTimeout(window.UpdateOutput,2000,"\\gamma");
