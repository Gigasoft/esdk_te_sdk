
define(["service/system"], function(system){
    
    var inner = '<div id="item-body_{guid}" class="item-body item-body-system">' +
                    '<span id="meeting-notify-text_{guid}" class="meeting-notify-text">{notifyText}</span>' +
					'<span id="meeting-attendee_{guid}" class="meeting-attendee">{members}</span>' +
                    '<span class="im-time">{time}</span>' +
                '</div>'  ,
    
    meeting = {
        
        getDOM: function(options){
            
            var dom, lang = system.getLang(), members = options.members ? options.members.join(", ") : "";
            
            dom = document.createElement("div") ;
            dom.id = "item_" + options.guid ;
            dom.className = "item item-system" ;
            
            dom.innerHTML = inner.replace(/{guid}/g, options.guid)
                                 .replace(/{notifyText}/, lang[options.type.toUpperCase().replace(/\-/g, "_")])
                                 .replace(/{members}/, members)
                                 .replace(/{time}/g, options.time);
            
            return dom ;
            
        },
        
        changeState: function(){
            
            
            
        }
            
    } ;
    
    return meeting ;
    
}) ;