
define(["service/system", "util/util"], function(system, util){
    var title = '<span id="item-title_{guid}" class="{titleColor}">{name} {time}</span>',
    
    body = '<div id="item-body_{guid}" class="item-body">' +
                '<span id="im-content_{guid}" class="im-content">{content}</span>{showContext}' +
           '</div>' ;
    
    var im = {

        getDOM: function(record, joinRecord){
            
            var dom,
            titleColor = (system.getInfo().account == record.account) ? "im-title-sender" : "im-title-receiver",
            lang = system.getLang(),
            titleHTML = title,
            bodyHTML = body;
            
            dom = document.createElement("div") ;
            dom.id = "item_" + record.guid ;
            dom.className = "item" ;
            

            if( joinRecord )
            {
                titleHTML = "" ;
            }
            else
            {
                titleHTML = titleHTML.replace(/{guid}/g, record.guid)
                                     .replace(/{name}/, record.name) 
                                     .replace(/{time}/, record.time)
                                     .replace(/{titleColor}/, titleColor) ;
            }
            
            bodyHTML = bodyHTML.replace(/{content}/, util.highlightContent(record.content, record.keyword).replace(/\$/g, "$$$$"))
                               .replace(/{showContext}/, record.showContext ? '<a id="im-show-context_{guid}" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "")
                               .replace(/{guid}/g, record.guid);
            
            dom.innerHTML = titleHTML + bodyHTML ;
            
            return dom ;
            
        },
        
        changeState: function(){
            
        }
    } ;
    
    return im ;
}) ;