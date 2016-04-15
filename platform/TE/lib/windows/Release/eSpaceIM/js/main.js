

require.config({
    baseUrl : "../js",
    waitSeconds : 10
});

require(["io/io", "component/scrollbar", "util/empty-function"], function(io, scrollbar){
    io.init() ;

    io.send("<root __type__=\"page-load-complete\"></root>") ;
}) ;


		function ShowImage(domObj){
			var imgSRC=domObj.src;
			var width = domObj.width;
			var height = domObj.height; 
			window.external.ShowPicture(imgSRC,width,height);  
		}
		

		function ShowImageMenu(domObj){
		    var e=window.event;
			if(e.button == '1')
			{
			  ShowImage(domObj);
			}
			else if(e.button == '2')
			{
			  var imgSRC=domObj.src;
              window.external.ShowPictureMenu(imgSRC, domObj.outerHTML);
			}
		}