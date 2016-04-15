
define(["service/system"], function(system){
    var inner = '<div id="item-body_{guid}" class="item-body item-body-system">' +
                    '<span id="call-text_{guid}" class="call-text {callImage}">{callText} {duration}</span>' +
                    '<span class="im-time">{time}</span>' +
                '</div>',
    
    call = {
        getDOM: function(options){
            
            var dom, lang = system.getLang() ;
            
            dom = document.createElement("div") ;
            dom.id = "item_" + options.guid ;
            dom.className = "item item-system" ;
            
            dom.innerHTML = inner.replace(/{guid}/g, options.guid)
                                 .replace(/{callImage}/g, options.type + "-img")
                                 .replace(/{callText}/g, lang[options.type.toUpperCase().replace(/\-/g, "_")])
                                 .replace(/{time}/g, options.time)
                                 .replace(/{duration}/g, options.duration ? options.duration : "") ;
            
            return dom ;
        },
        
        changeState: function(id, state){
            
        }
    } ;
    
    return call ;
}) ;