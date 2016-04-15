
define([], function(){

    function now()
    {
        return (new Date()).getTime() ;
    }
    

    function getId(id)
    {
        return id.split("_")[1] ;
    }
    

    function highlightContent(content, keyword)
    {
        var html = "" ;

        if(keyword)
        {
            var node = document.createElement("div") ;
            
            node.innerHTML = content ;
            
            highlightKeyword(node, node, keyword) ;
            
            html = node.innerHTML ;
        }
        else
        {
            html = content ;
        }
        
        return html ;
    }
    

    function highlightKeyword(node, parentNode, keyword)
    {
        if(node.nodeType == "3" && node.nodeValue.search(new RegExp("(" + keyword + ")+", "i")) != -1)
        {
            var element = document.createElement("span") ;
            
            element.innerHTML = node.nodeValue.replace(new RegExp("(" + keyword.replace(/\$/g, "\\$") + ")+", "ig"),
                    function($0){
                        
                        return "<span class='keyword'>" + $0 + "</span>" ;
                        
                    }) ;
            
            parentNode.replaceChild(element, node) ;
            
            return ;
        }
        
        for(var i=0; i<node.childNodes.length; i++)
        {
            highlightKeyword(node.childNodes[i], node, keyword) ;
        }
    }
    

    function extend(destObj, srcObj)
    {
        for(var i in srcObj)
        {
            destObj[i] = srcObj[i] ;
        }
    }
    
    return {
        now: now,
        getId: getId,
        highlightContent: highlightContent,
        extend: extend
    } ;
}) ;