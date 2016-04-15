
define(["service/system"], function(system){
    
    var inner = '<div id="item-body_{guid}" class="item-body item-body-system">' +
                    '<span id="record-text_{guid}" class="record-text">{prefixText}<a id="record-path_{guid}" actionType="record-open" class="record-path" title="{recordPath}" >{recordPath}</a></span>' +
                    '<span class="im-time">{time}</span>' +
                '</div>' ,
    
    record = {
        
        getDOM: function(options){
            
            var dom, lang = system.getLang(), members = options.members ? options.members.join(", ") : "";
            
            dom = document.createElement("div") ;
            dom.id = "item_" + options.guid ;
            dom.className = "item item-system" ;
            
            dom.innerHTML = inner.replace(/{guid}/g, options.guid)
                                 .replace(/{prefixText}/g, members + lang[options.type.toUpperCase().replace(/\-/g, "_")])
                                 .replace(/{recordPath}/g, options.filePath)
                                 .replace(/{time}/g, options.time);
            
            return dom ;
            
        },
        
        changeState: function(){
            
        }
    } ;
    
    return record ;
}) ;