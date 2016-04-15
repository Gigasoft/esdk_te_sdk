
define(["component/dd"], function(DD){
    
    var Scroll = {

        scrollArea: "",
        

        scrollContainer: "",

        scrollBody: "",
        

        startPos: {},

        moveDistancePerAction: 20,
        

        moveDistance: 20,

        moveTimer: null,
        

        moveInterval: 50,
        

        moveDirection: null ,
        
        up: -1,
        
        down: 1,
        

        scrollBodyCornerHeight: 3,
        

        state: "normal",
        

        config: {},
        

        init: function(options){
            
            this.createDOM() ;
            

            this.scrollArea = options.scrollArea ;
            this.scrollContainer = document.getElementById("scroll-container") ;
            this.scrollBody = document.getElementById("scroll-body") ;
            this.scrollBodyMid = document.getElementById("scroll-body-mid") ;
            
            Util.bind(window, "load", this.onBrowserResize) ;
            Util.bind(this.scrollBody, "mousedown", this.startDrag) ;
            Util.bind(this.scrollBody, "mouseover", this.scrollBodyHover) ;
            Util.bind(this.scrollBody, "mouseout", this.scrollBodyNormal) ;
            

            Util.bind(this.scrollContainer, "mousedown", this.startMove) ;
            Util.bind(this.scrollContainer, "mouseup", this.stopMove) ;
            
 
            Util.bind(document, "keydown", this.startMove) ;
            Util.bind(document, "keyup", this.stopMove) ;
            

            Util.bind(this.scrollArea, "mousewheel", this.mouseWheel) ;

            
            
            Util.bind(window, "resize", this.onBrowserResize) ;
            Util.bind(this.scrollArea, "resize", this.onBrowserResize) ;
            
            Util.bind(this.scrollArea, "scroll", this.onScroll) ;
            
            Scroll.config = {} ;
            
            this.onBrowserResize() ;
        },
        
        createDOM: function(){
            
            var dom = document.createElement("div") ;
            
            dom.id = "scroll-container" ;
            dom.className = "scroll-container" ;
            dom.innerHTML = '<div id="scroll-body" class="scroll-body" oncontrolselect="return false;">' +
                                '<div class="scroll-body-up"></div>' +
                                '<div id="scroll-body-mid" class="scroll-body-mid"></div>' +
                                '<div class="scroll-body-down"></div>' +
                            '</div>' ;
            
            document.getElementsByTagName("body")[0].appendChild(dom) ;
            
        },
        
        scrollBodyHover: function(){
            Scroll.scrollBody.className = "scroll-body scroll-body-hover" ;
        },
        
        scrollBodyNormal: function(){
            Scroll.scrollBody.className = "scroll-body" ;
        },
        
        startDrag: function(event){
            event = event || window.event ;
            
            var p = Util.getPointer(event) ;

            Scroll.startPos.top = Util.css(Scroll.scrollBody, "top") ;
            Scroll.startPos.left = Util.css(Scroll.scrollBody, "left");
            Scroll.startPos.x = p.x ;
            Scroll.startPos.y = p.y ;
            
            Util.bind(document, "mousemove", Scroll.moveDrag) ;
            Util.bind(document, "mouseup", Scroll.stopDrag) ;

            Util.bind(Scroll.scrollBody, "losecapture", Scroll.moveDrag);

            Scroll.scrollBody.setCapture();
            
            event.cancelBubble = true;

            Scroll.scrollBody.className = "scroll-body scroll-body-active" ;
        },
        
        moveDrag: function(event){
            event = event || window.event ;
            window.getSelection ? window.getSelection().removeAllRanges() : document.selection.empty();
            var newPos = {} ;
            var p = Util.getPointer(event) ;
            
            newPos.top = Scroll.startPos.top - Scroll.startPos.y + p.y;
            newPos.left = Scroll.startPos.left - Scroll.startPos.x + p.x;  
            
            Scroll.scrollArea.scrollTop = newPos.top * Scroll.moveDistance ;
            
            var maxTop = (parseInt(Scroll.scrollContainer.offsetHeight) || 0) - Util.css(Scroll.scrollBody, "height") ;
            newPos.top = (newPos.top < 0) ? 0 : newPos.top ;
            newPos.top = (newPos.top > maxTop) ? maxTop : newPos.top ;
            
            Util.css(Scroll.scrollBody, "top", newPos.top) ;
        },
        
        stopDrag: function(event){
            Util.unbind(document, "mousemove", Scroll.moveDrag) ;
            Util.unbind(document, "mouseup", Scroll.stopDrag) ;
            

            Util.unbind(Scroll.scrollBody, "losecapture", Scroll.moveDrag);

            Scroll.scrollBody.releaseCapture();
            
            Scroll.scrollBodyNormal() ;
        },
        

        startMove: function(event){
            event = event || window.event ;
            
            var p = {} ;
            
            if(event.type == "mousedown")
            {
                clearInterval(Scroll.moveTimer) ;
                p = Util.getPointer(event) ;
                
                Scroll.moveDirection = (p.y < Util.css(Scroll.scrollBody, "top")) ? Scroll.up : Scroll.down ;
                
                Scroll.moveTimer = setInterval(Scroll.scrollMoveTimer, Scroll.moveInterval) ;
            }

            else if(event.type == "keydown")
            {
                if(event.keyCode == 40)
                {
                    Scroll.moveDirection = Scroll.down ;
                }
                else if(event.keyCode == 38)
                {
                    Scroll.moveDirection = Scroll.up ;
                }
                
                Scroll.updateScroll() ;
            }
            
            Scroll.startPos.y = p.y ;
        },
        
        scrollMoveTimer: function(){
            
            if(Scroll.moveDirection == Scroll.up && (Util.css(Scroll.scrollBody, "top") <= Scroll.startPos.y)
                || Scroll.moveDirection == Scroll.down && (Util.css(Scroll.scrollBody, "top") + Util.css(Scroll.scrollBody, "height") >= Scroll.startPos.y))
            {
                clearInterval(Scroll.moveTimer) ;
            }
            else
            {
                Scroll.updateScroll() ;
            }
        },
        
        stopMove: function(){
            clearInterval(Scroll.moveTimer) ;
        },
        

        mouseWheel: function(event){
            event = event || window.event ;
            
            var dis = (event.wheelDelta > 0) ? -Scroll.moveDistancePerAction : Scroll.moveDistancePerAction ;
            var newPos = {} ;
            
            Scroll.moveDirection = (event.wheelDelta > 0) ? Scroll.up : Scroll.down ;
            
            Scroll.scrollArea.scrollTop += Scroll.moveDirection * Scroll.moveDistancePerAction ;
            Util.css(Scroll.scrollBody, "top", Math.floor(Scroll.scrollArea.scrollTop / Scroll.moveDistance)) ;
            
            if(typeof Scroll.config.onMouseWheel === "function")
            {
                Scroll.config.onMouseWheel.call(Scroll, Scroll) ; 
            }
        },
        
        updateScroll: function(){
            Scroll.scrollArea.scrollTop += Scroll.moveDirection * Scroll.moveDistancePerAction ;
            Util.css(Scroll.scrollBody, "top", Math.floor(Scroll.scrollArea.scrollTop / Scroll.moveDistance)) ;
        },
        

        onBrowserResize: function(){
            var d = Util.getWindowDimension() ;
            

            if(Scroll.scrollArea.scrollHeight <= d.height)
            {
                Scroll.scrollBody.style.display = "none" ;
                return ;
            }
            
            Scroll.scrollBody.style.display = "block" ;
            
            var scrollBodyHeight = Math.floor(Math.pow(d.height, 2) / Scroll.scrollArea.scrollHeight) ;
            scrollBodyHeight = (scrollBodyHeight < 2*Scroll.scrollBodyCornerHeight) ? 2*Scroll.scrollBodyCornerHeight : scrollBodyHeight ;
            
            Scroll.moveDistance = (Scroll.scrollArea.scrollHeight - Scroll.scrollArea.offsetHeight) / (d.height - scrollBodyHeight) ;

            var scrollBodyTop = Math.floor(Scroll.scrollArea.scrollTop / Scroll.moveDistance) ;
            scrollBodyTop = isNaN(scrollBodyTop) ? 0 : scrollBodyTop ;
            Util.css(Scroll.scrollBody, "top", scrollBodyTop) ;
            
            Util.css(Scroll.scrollBody, "height", scrollBodyHeight) ;
            Util.css(Scroll.scrollBodyMid, "height", scrollBodyHeight - 2*Scroll.scrollBodyCornerHeight) ;
        },
        

        onScroll: function(){

        },
        

        toBottom: function(){
            Scroll.onBrowserResize() ;
            
            var maxTop = (parseInt(Scroll.scrollContainer.offsetHeight) || 0) - Util.css(Scroll.scrollBody, "height") ;
            
            Util.css(Scroll.scrollBody, "top", maxTop) ;
            Scroll.scrollArea.scrollTop = Scroll.scrollArea.scrollHeight ;
        },
        

        toTop: function(){
            Scroll.onBrowserResize() ;
            Scroll.scrollArea.scrollTop = 0 ;
            Util.css(Scroll.scrollBody, "top", 0) ;
        },
        

        prepend: function(data){
            
        },
        

        append: function(data){
            
        },
        
        clear: function(){
            var area = document.getElementById("scroll-area") ;
            area.innerHTML = "" ;
        }
    },

    Util = {

        getWindowDimension: function(){
            return {
                width: parseInt(document.documentElement.clientWidth) || 0,
                height: parseInt(document.documentElement.clientHeight) || 0
            } ;
        },
        
        getPointer: function(event){
            var doc = document.documentElement, body = document.body;
            
            event.pageX = event.clientX + (doc && doc.scrollLeft || body && body.scrollLeft || 0) - (doc && doc.clientLeft || body && body.clientLeft || 0);
            event.pageY = event.clientY + (doc && doc.scrollTop  || body && body.scrollTop  || 0) - (doc && doc.clientTop  || body && body.clientTop  || 0);
            
            var x = event.pageX || (event.clientX + (document.documentElement.scrollLeft || document.body.scrollLeft)) || 0;
            var y = event.pageY || (event.clientY + (document.documentElement.scrollTop || document.body.scrollTop)) || 0;
            
            return {x:x, y:y};
        },
        

        bind: function(obj, eventType, callBack){
            if(window.attachEvent)
            {
                obj.attachEvent("on" + eventType, callBack) ;
            }
            else if(window.addEventListener)
            {
                obj.addEventListener(eventType, callBack, false) ;
            }
        },
        

        unbind: function(obj, eventType, callBack){
            if(window.detachEvent)
            {
                obj.detachEvent("on" + eventType, callBack) ;
            }
            else if(window.removeEventListener)
            {
                obj.removeEventListener(eventType, callBack, false) ;
            }
        },
        
        css: function(obj, name, value){
            if(value != null)
            {
                obj.style[name] = (typeof value === "number") ? (value + "px") : value;
            }
            else
            {
                var style = 0 ;
                style = (obj.currentStyle) ? obj.currentStyle.getAttribute(name) : window.getComputedStyle(obj, null).getPropertyValue(name) ;
                
                return parseInt(style) || 0 ;
            }
        }
    } ;

    return Scroll ;
    
}) ;