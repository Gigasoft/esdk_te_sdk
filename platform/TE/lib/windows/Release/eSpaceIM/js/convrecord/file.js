
define(["service/system", "util/util"], function(system, util){
    
    var title = '<span id="item-title_{guid}" class="item-title {titleColor}">{name} {time}</span>',
    
    file = {
        

        getDOM: function(record, joinRecord){
            
            var dom,
            titleColor = (system.getInfo().account == record.account) ? "im-title-sender" : "im-title-receiver",
            lang = system.getLang(),
            titleHTML = title,
            bodyHTML ;
            
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
            
            bodyHTML = '<div id="item-body_' + record.guid + '" class="item-body item-body-file">' + 
                            stateHTML[record.type.replace(/\-/g, "_")](record) + 
                       '</div>' ;
            
            dom.innerHTML = titleHTML + bodyHTML ;
            
            return dom ;
            
        },
        
        changeState: function(options){

            document.getElementById("item-body_" + options.guid).innerHTML = stateHTML[options.type.replace(/\-/g, "_")](options) ;
            
        },
        
        progress: function(options){
            
            var progressbarM = document.getElementById("progressbar-c-m_" + options.guid),
            progressbarR = document.getElementById("progressbar-c-r_" + options.guid),
            fileSpeed = document.getElementById("file-speed_" + options.guid),
            
            moveDistance = 72,  
            progressbarLeftWidth = 5,   
            
            lang = system.getLang() ;
            
            progressbarM.style.width = options.fileSavePercent * 72 + "px" ;
            progressbarR.style.left = progressbarM.offsetWidth + progressbarLeftWidth + "px" ;
            
            fileSpeed.innerHTML = "(" + options.fileSpeed + ")" ;
            

            document.getElementById("file-state-text_" + options.guid).innerHTML = lang[options.type.toUpperCase().replace(/\-/g, "_")] ;
            

            document.getElementById("file-name_" + options.guid).innerHTML = 
                options.fileName + " (" + (options.fileSize || "") + ")" ;
            
        }
    } ,
    

    stateHTML = {
        
        "file_send_wait" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                   '<a actionType="file-stop" title="' + lang.FILE_CANCEL + '" id="file-stop_' + record.guid + '"  class="file-stop file-stop-normal"></a>' ;
            
        },
        
        "file_send_reject" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' ;
            
        },
        
        "file_send_cancel" : function(record){
            
            return this["file_send_sender_stop"](record)  ;
            
        },
        
        "file_send_sender_stop" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                   '<a actionType="file-send-again" title="' + lang.FILE_SEND_AGAIN + '" id="msg-error_' + record.guid + '"  class="msg-error msg-error-normal"></a>' ;
            
        },
        
        "file_send_receiver_stop" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' ;
            
        },
        
        "file_send_progress" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                    '<div id="progressbar_' + record.guid + '" class="progressbar">' + 
                        '<div id="progressbar-c-l_' + record.guid + '" class="progressbar-c-l"></div>' + 
                        '<div id="progressbar-c-m_' + record.guid + '" class="progressbar-c-m"></div>' + 
                        '<div id="progressbar-c-r_' + record.guid + '" class="progressbar-c-r"></div>' +
                    '</div>' +
                    '<span id="file-speed_' + record.guid + '" class="file-speed">' + "(" + record.fileSpeed + ")" + '</span>' +
                    '<a actionType="file-stop" title="' + lang.FILE_CANCEL + '" id="file-stop_' + record.guid + '"  class="file-stop file-stop-normal"></a>' ;
            
        },
        
        "file_send_success" : function(record){
            
            return this["file_send_receiver_stop"](record)  ;
            
        },
        
        "file_send_error" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                   '<a actionType="file-send-again" title="' + lang.FILE_SEND_AGAIN + '" id="msg-error_' + record.guid + '"  class="msg-error msg-error-normal"></a>' ;
            
        },
        
        "file_space_not_enough" : function(record){
            
            return this["file_send_receiver_stop"](record)  ;
            
        },
        
        "file_not_exist" : function(record){
            
            return this["file_send_receiver_stop"](record)  ;
            
        },
        
        "file_send_failed" : function(record){
            
            return this["file_send_receiver_stop"](record)  ;
            
        },
        
        "file_send_no_permission" : function(record){
            
            return this["file_send_receiver_stop"](record)  ;
            
        },
		
		"file_send_too_large" : function(record){
            
            return this["file_send_receiver_stop"](record)  ;
            
        },
        

        "file_receive_wait" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                   '<div id="receive-wait-buttons_' + record.guid + '" class="receive-wait-buttons">' +
                       '<input actionType="file-accept" id="button-accept_' + record.guid + '" class="button button-normal button-accept" type="button" value="' + lang.FILE_ACCEPT + '"/>' +
                       '<input actionType="file-save" id="button-save_' + record.guid + '" class="button button-normal button-save" type="button" value="' + lang.FILE_SAVE + '"/>' +
                       '<input actionType="file-reject" id="button-reject_' + record.guid + '" class="button button-normal button-reject" type="button" value="' + lang.FILE_REJECT + '"/>' +
                   '</div>' +
                   (record.fileOffline ? '<div class="file-expire">' + lang.FILE_EXPIRED.replace(/{expiredTime}/, record.fileExpiredTime) + '</div>' : "") ;
            
        },
        
        "file_receive_reject" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' ;
            
        },
        
        "file_receive_cancel" : function(record){
            
            return this["file_receive_reject"](record) ;
            
        },
        
        "file_receive_sender_stop" : function(record){
            
            return this["file_receive_reject"](record) ;
            
        },
        
        "file_receive_receiver_stop" : function(record){
            
            return this["file_receive_reject"](record) ;
            
        },
        
        "file_receive_progress" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                   '<div id="progressbar_' + record.guid + '" class="progressbar">' + 
                       '<div id="progressbar-c-l_' + record.guid + '" class="progressbar-c-l"></div>' + 
                       '<div id="progressbar-c-m_' + record.guid + '" class="progressbar-c-m"></div>' + 
                       '<div id="progressbar-c-r_' + record.guid + '" class="progressbar-c-r"></div>' +
                   '</div>' +
                   '<span id="file-speed_' + record.guid + '" class="file-speed">' + "(" + record.fileSpeed + ")" + '</span>' +
                   '<a actionType="file-stop" title="' + lang.FILE_CANCEL + '" id="file-stop_' + record.guid + '" class="file-stop file-stop-normal"></a>' ;
            
        },
        
        "file_receive_success" : function(record){
            
            var lang = system.getLang() ;
            
            return '<img id="preview-img_' + record.guid + '" class="preview-img" src="' + record.fileImagePath + '"/>' +
                   ( record.showContext ? '<a id="im-show-context_' + record.guid + '" actionType="show-context" class="im-show-context">' + lang.SHOW_CONTEXT + '</a>' : "" ) +
                   '<span id="file-name_' + record.guid + '" class="file-name">' + (record.keyword ? util.highlightContent(record.fileName, record.keyword).replace(/\$/g, "$$$$") : record.fileName) + ' (' + record.fileSize + ')</span>' +
                   '<span id="file-state-text_' + record.guid + '" class="file-state-text">' + lang[record.type.toUpperCase().replace(/\-/g, "_")] + '</span>' +
                   '<div id="receive-success-buttons_' + record.guid + '" class="receive-success-buttons">' +
                       '<input actionType="file-open" id="button-open_' + record.guid + '" class="button button-xl-normal button-file-open" type="button" value="' + lang.FILE_OPEN + '"/>' +
                       '<input actionType="file-open-folder" id="button-open-folder_' + record.guid + '" class="button button-xl-normal button-open-folder" type="button" value="' + lang.FILE_OPEN_FOLDER + '"/>' +
                   '</div>' ;
            
        },
        
        "file_receive_error" : function(record){
            
            return this["file_receive_reject"](record) ;
            
        },
		
		"file_receive_not_exist" : function(record){
            
            return this["file_receive_reject"](record) ;
            
        }
        
    } ;
    
    return file ;
    
}) ;
