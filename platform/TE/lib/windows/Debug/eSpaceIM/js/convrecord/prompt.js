
define([], function(){
    
    var inner = '<div id="item-body_{guid}" class="item-body item-body-system">' +
                    '<span id="prompt-text_{guid}" class="prompt-text">{promptText}</span>' +
                    '<span class="im-time">{time}</span>' +
                '</div>' ,
    
    prompt = {
        
        getDOM: function(options){
            
            var dom ;
            
            dom = document.createElement("div") ;
            dom.id = "item_" + options.guid ;
            dom.className = "item item-system" ;
            
            dom.innerHTML = inner.replace(/{guid}/g, options.guid)
                                 .replace(/{promptText}/g, options.content)
                                 .replace(/{time}/g, options.time);
            
            return dom ;
            
        },
        
        changeState: function(){
            
        }
    } ;
    
    return prompt ;
}) ;