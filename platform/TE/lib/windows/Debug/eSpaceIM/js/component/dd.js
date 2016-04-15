
define([], function(){
    
    var isIE = document.all ? true : false ;
    
    function $(id)
    {
        return document.getElementById(id) ;
    }
    

    function bind(obj, eventType, callback)
    {
        if(obj.addEventListener)
        {
            obj.addEventListener(eventType, callback, false) ;
        }
        else if(obj.attachEvent)
        {
            obj.attachEvent("on" + eventType, callback) ;
        }
        else
        {
            obj["on" + eventType] = callback ;
        }
    }
    

    function unbind(obj, eventType, callback)
    {
        if (obj.removeEventListener)
        {
            obj.removeEventListener(eventType, callback, false);
        }
        else if (obj.detachEvent)
        {
            obj.detachEvent("on" + eventType, callback);
        }
        else
        { 
            obj["on" + eventType] = null;
        }
    }
    

    function _bindEvent(obj, fun)
    {
        return function(event){
            event = event || window.event ;
            event.target = event.srcElement || event.target ;
            fun.call(obj, event) ;
        } ;
    }
    

    function css(obj, name, value){
        if(value != null)
        {
            obj.style[name] = (typeof value === "number") ? (value + "px") : value;
        }
        else
        {
            var style = 0 ;
            style = (obj.currentStyle) ? obj.currentStyle[name] : window.getComputedStyle(obj, null).getPropertyValue(name) ;
            
            return parseInt(style) || 0 ;
        }
    }
    

    function getPointer(event)
    {
        return {
            x: event.pageX || (event.clientX + (document.documentElement.scrollLeft || document.body.scrollLeft)) || 0,
            y: event.pageY || (event.clientY + (document.documentElement.scrollTop || document.body.scrollTop)) || 0
        } ;
    }

    function executeFunc(func, context, arguments)
    {
        var result = (typeof func === "function") ? func.apply(context, arguments) : func ;
        return (typeof result === "number") ? result : func ;
    }
    

    var changeAttr = {
        n: function(pointer){

            var pos = changeAttr.getNewPosition.call(this, pointer),
                dim = changeAttr.getNewDimension.call(this, pointer, "n");
            
            if(pos.top < this.maxTop && pos.top > this.minTop 
                && dim.height < this.maxHeight && dim.height > this.minHeight)
            {
                this.element.style.top = pos.top + "px";
                this.element.style.height = dim.height + "px";
            }
        },
        
        s: function(pointer){

            this.element.style.height = changeAttr.getNewDimension.call(this, pointer).height + "px" ;
        },
        
        w: function(pointer){

            var pos = changeAttr.getNewPosition.call(this, pointer),
                dim = changeAttr.getNewDimension.call(this, pointer, "w");
            
            if(pos.left < this.maxLeft && pos.left > this.minLeft 
                && dim.width < this.maxWidth && dim.width > this.minWidth)
            {
                this.element.style.left = pos.left + "px";
                this.element.style.width = dim.width + "px";
            }
        },
        
        e: function(pointer){

            this.element.style.width = changeAttr.getNewDimension.call(this, pointer).width + "px" ;
        },
        
        nw: function(pointer){

            var pos = changeAttr.getNewPosition.call(this, pointer),
                dim = changeAttr.getNewDimension.call(this, pointer, "nw");
            
            if(pos.top < this.maxTop && pos.top > this.minTop
                && dim.height < this.maxHeight && dim.height > this.minHeight)
            {
                this.element.style.top = pos.top + "px";
                this.element.style.height = dim.height + "px";
            }
            
            if(pos.left < this.maxLeft && pos.left > this.minLeft
                && dim.width < this.maxWidth && dim.width > this.minWidth)
            {
                this.element.style.left = pos.left + "px";
                this.element.style.width = dim.width + "px";
            }
        },
        
        ne: function(pointer){

            var pos = changeAttr.getNewPosition.call(this, pointer),
                dim = changeAttr.getNewDimension.call(this, pointer, "ne");
            
            if(pos.top < this.maxTop && pos.top > this.minTop
                && dim.height < this.maxHeight && dim.height > this.minHeight)
            {
                this.element.style.top = pos.top + "px";
                this.element.style.height = dim.height + "px";
            }
            
            if(dim.width < this.maxWidth && dim.width > this.minWidth)
            {
                this.element.style.width = dim.width + "px";
            }
        },
        
        sw: function(pointer){

            var pos = changeAttr.getNewPosition.call(this, pointer),
            dim = changeAttr.getNewDimension.call(this, pointer, "sw");
        
            if(dim.height < this.maxHeight && dim.height > this.minHeight)
            {
                this.element.style.height = dim.height + "px";
            }
            
            if(pos.left < this.maxLeft && pos.left > this.minLeft
                    && dim.width < this.maxWidth && dim.width > this.minWidth)
            {
                this.element.style.left = pos.left + "px";
                this.element.style.width = dim.width + "px";
            }
        },
        
        se: function(pointer){

            var dim = changeAttr.getNewDimension.call(this, pointer, "se");
            
            this.element.style.width = dim.width + "px";
            this.element.style.height = dim.height + "px";
        },
        
        getNewDimension: function(pointer, direction){
            var newWidth, newHeight,
                moveWidth = moveHeight = 0;
            
            newWidth = css(this.element, "width") ;
            newHeight = css(this.element, "height") ;
            
            if(!this.options.lockWidth)
            {
                moveWidth = this.cache.x - pointer.x ;
                moveWidth = (direction == "w" || direction == "nw" || direction == "sw") ? moveWidth : -moveWidth ;
                newWidth = this.cache.width + moveWidth;
                newWidth = Math.max(Math.min(this.maxWidth, newWidth), this.minWidth) ;
            }
            
            if(!this.options.lockHeight)
            {
                moveHeight = this.cache.y - pointer.y ;
                moveHeight = (direction == "n" || direction == "nw" || direction == "ne") ? moveHeight : -moveHeight ;
                newHeight = this.cache.height + moveHeight ;
                newHeight = Math.max(Math.min(this.maxHeight, newHeight), this.minHeight) ;
            }
            
            return {
                width: newWidth,
                height: newHeight,
                moveWidth: moveWidth,
                moveHeight: moveHeight
            } ;
        },
        
        getNewPosition: function(pointer){
            var newTop = this.cache.top,
                newLeft = this.cache.left, 
                moveTop = moveLeft = 0;
            
            if(!this.options.lockY)
            {
                moveTop = pointer.y - this.cache.y ;
                newTop = this.cache.top + moveTop;
                newTop = Math.max(Math.min(this.maxTop, newTop), this.minTop) ;
            }
            
            if(!this.options.lockX)
            {
                moveLeft = pointer.x - this.cache.x ;
                newLeft = this.cache.left + moveLeft ;
                newLeft = Math.max(Math.min(this.maxLeft, newLeft), this.minLeft) ;
            }
            
            return {
                top: newTop,
                left: newLeft,
                moveTop: moveTop,
                moveLeft: moveLeft
            } ;
        }
    } ;
    
    function DD(options)
    {
        this.init(options) ;
    }
    
    DD.prototype = {
        
        cache: {} ,

        init: function(options){
            this.options = options ;
            
            this.options.minTop = options.minTop || -10000;
            this.options.maxTop = options.maxTop || 10000;
            this.options.minLeft = options.minLeft || -10000;
            this.options.maxLeft = options.maxLeft || 10000;
            
            this.options.minWidth = options.minWidth || 200;
            this.options.maxWidth = options.maxWidth || 10000;
            this.options.minHeight = options.minHeight || 200;
            this.options.maxHeight = options.maxHeight || 10000;
            
            this.options.lockX = options.lockX || false ;
            this.options.lockY = options.lockY || false ;
            this.options.lockWidth = options.lockWidth || false ;
            this.options.lockHeight = options.lockHeight || false ;
            
            this.element = $(this.options.id) ;
            this.handleObj = $(this.options.handle) ;
            
            this.addEventListener() ;
        },

        addEventListener: function(){
            var direct = this.options.resizeDirect ? this.options.resizeDirect.split(" ") : [], i ;

            if(this.options.draggable)
            {
                bind(this.handleObj, "mousedown", _bindEvent(this, this.onDragStart)) ;
            }

            if(this.options.resizable)
            {
                for(i=0; i<direct.length; i++)
                {
                    bind($(this.options.id + "-resize-" + direct[i]), "mousedown", _bindEvent(this, this.onResizeStart)) ;
                }
            }
        },
        

        onDragStart: function(event){
            if(this.lockX && this.lockY)
                return ;
            
            var pointer = getPointer(event);
            
            this._onDrag = _bindEvent(this, this.onDrag) ;
            this._onDragStop = _bindEvent(this, this.onDragStop) ;
            
            bind(document, "mousemove", this._onDrag) ;
            bind(document, "mouseup", this._onDragStop) ;
            
            this.cache.top = css(this.element, "top") ;
            this.cache.left = css(this.element, "left") ;
            this.cache.x = pointer.x ;
            this.cache.y = pointer.y ;
            
            this.minTop = executeFunc(this.options.minTop, this, [event]) ;
            this.maxTop = executeFunc(this.options.maxTop, this, [event]) ;
            this.minLeft = executeFunc(this.options.minLeft, this, [event]) ;
            this.maxLeft = executeFunc(this.options.maxLeft, this, [event]) ;
            

            if(isIE)
            {
                bind(this.handleObj, "losecapture", this._onDragStop) ;
                this.handleObj.setCapture();
            }

            else
            {
                bind(window, "blur", this._onDragStop);
                event.preventDefault();
            }
            
            executeFunc(this.options.onDragStart, this, [event]) ;
        },
        

        onDrag: function(event){
            var pos ;
            
            window.getSelection ? window.getSelection().removeAllRanges() : document.selection.empty();
            
            if(!this.options.lockY || !this.options.lockX)
                pos = changeAttr.getNewPosition.call(this, getPointer(event)) ;
            
            if(!this.options.lockY)
                this.element.style.top = pos.top + 'px';
            if(!this.options.lockX)
                this.element.style.left = pos.left + 'px';
            
            executeFunc(this.options.onDrag, this, [event, pos]) ;
        },
        

        onDragStop: function(event){
            unbind(document, "mousemove", this._onDrag) ;
            unbind(document, "mouseup", this._onDragStop) ;
            

            if(isIE)
            {
                unbind(this.handleObj, "losecapture", this._onDragStop) ;
                this.handleObj.releaseCapture();
            }

            else
            {
                unbind(window, "blur", this._onDragStop) ;
            }
            
            executeFunc(this.options.onDragStop, this, [event]) ;
        },
        

        onResizeStart: function(event){
            if(this.lock)
                return ;
            
            var pointer = getPointer(event) ;
            
            this._onResize = _bindEvent(this, this.onResize) ;
            this._onResizeStop = _bindEvent(this, this.onResizeStop) ;
            
            this.cache.x = pointer.x ;
            this.cache.y = pointer.y ;
            this.cache.top = css(this.element, "top") ;
            this.cache.left = css(this.element, "left") ;
            this.cache.width = css(this.element, "width") ;
            this.cache.height = css(this.element, "height") ;
            this.cache.resizeId = event.target.id.split("-")[2] ;
            
            this.minTop = executeFunc(this.options.minTop, this, [event]) ;
            this.maxTop = executeFunc(this.options.maxTop, this, [event]) ;
            this.minLeft = executeFunc(this.options.minLeft, this, [event]) ;
            this.maxLeft = executeFunc(this.options.maxLeft, this, [event]) ;
            
            this.minWidth = executeFunc(this.options.minWidth, this, [event]) ;
            this.maxWidth = executeFunc(this.options.maxWidth, this, [event]) ;
            this.minHeight = executeFunc(this.options.minHeight, this, [event]) ;
            this.maxHeight = executeFunc(this.options.maxHeight, this, [event]) ;
            
            bind(document, "mousemove", this._onResize) ;
            bind(document, "mouseup", this._onResizeStop) ;
            
            this.resizeHandleObj = $(this.options.id + "-resize-" + this.cache.resizeId) ;
            

            if(isIE)
            {
                bind(this.resizeHandleObj, "losecapture", this._onResizeStop) ;
                this.resizeHandleObj.setCapture();
            }

            else
            {
                bind(window, "blur", this._onResizeStop);
                event.preventDefault();
            }
            
            executeFunc(this.options.onResizeStart, this, [event]) ;
        },

        onResize: function(event){
            changeAttr[this.cache.resizeId].call(this, getPointer(event));
            
            executeFunc(this.options.onResize, this, [event]) ;
        },
        

        onResizeStop: function(event){
            unbind(document, "mousemove", this._onResize) ;
            unbind(document, "mouseup", this._onResizeStop) ;
            

            if(isIE)
            {
                unbind(this.resizeHandleObj, "losecapture", this._onResizeStop) ;
                this.resizeHandleObj.releaseCapture();
            }

            else
            {
                unbind(window, "blur", this._onResizeStop) ;
            }
            
            executeFunc(this.options.onResizeStop, this, [event]) ;
        },

        freeze: function(){
            this.lockX = true ;
            this.lockY = true ;
        },
        

        unfreeze: function(){
            this.lockX = false ;
            this.lockY = false ;
        }
    } ;
    
    return DD ;
}) ;
