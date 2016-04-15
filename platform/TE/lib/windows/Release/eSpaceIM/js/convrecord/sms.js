
define(["service/system", "util/util"], function(system, util){
    
    var title = '<span id="item-title_{guid}" class="item-title {titleColor}">{name} {time}</span>',
    
    body = '<div id="item-body_{guid}" class="item-body {smsState}">' +
                '<a id="sms-state_{guid}" href="javascript:void(0)" class="sms-state" title="{smsStateTitle}" hideFocus="true"></a>' +
                '<span id="sms-content_{guid}" class="sms-content">{content}</span>{showContext}' +
                '<a id="msg-error_{guid}" actionType="sms-send-again" href="javascript:void(0)" class="msg-error msg-error-normal" title="{smsMsgError}" hideFocus="true"></a>' +
            '</div>',
    
    sms = {
        

        getDOM: function(record, joinRecord){
            
            var dom,
            lang = system.getLang(),
            titleColor = (system.getInfo().account == record.account) ? "im-title-sender" : "im-title-receiver",
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
            
            bodyHTML = bodyHTML.replace(/{showContext}/, record.showContext ? '<a id="im-show-context_{guid}" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "")
                               .replace(/{guid}/g, record.guid)
                               .replace(/{content}/, util.highlightContent(record.content, record.keyword).replace(/\$/g, "$$$$"))
                               .replace(/{smsState}/, "item-state-" + record.type + (record.hideRetry ? " no-retry-icon" : ""))
                               .replace(/{smsStateTitle}/, lang[record.type.toUpperCase().replace(/\-/g, "_")])
                               .replace(/{smsMsgError}/, lang.SMS_SEND_AGAIN)
                               ;
            
            dom.innerHTML = titleHTML + bodyHTML ;
            
            return dom ;
            
        },
        
        changeState: function(options){
            
            var lang = system.getLang() ;
			document.getElementById("item-body_" + options.body.id).className = 
                "item-body item-state-" + options.type + (options.hideRetry ? " no-retry-icon" : "");
            
            document.getElementById("sms-state_" + options.body.id).title = lang[options.type.toUpperCase().replace(/\-/g, "_")] ;
            
        }
    } ;
    
    return sms ;
}) ;