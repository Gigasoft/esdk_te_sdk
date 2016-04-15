
define(["util/util",
        "convrecord/im",
        "convrecord/sms",
        "convrecord/file",
        "convrecord/call",
        "convrecord/meeting",
        "convrecord/tape",
        "service/system"], 
        function(util,
                 im,
                 sms,
                 file,
                 call,
                 meeting,
                 tape,
                 system){
    
    var view = {

        init: function(options){
            this.container = document.getElementById("im-container") ;
            
            this.eventCallback = options.eventCallback ;
        },

        container: null,
        

        recordType: {
            IM: "im",
            SMS: "sms",
            FILE: "file",
            CALL: "call",
            MEETING: "meeting",
            TAPE: "tape"
        },
        

        records: {
            
        },
        

        latestRecord: {
            id: "",     
            time: ""   
        },

        recordMapping: {},

        eventCallback: {},
        

        actionType: {
            SMS_SEND_AGAIN: "sms_send_again",
            FILE_CANCEL: "file_cancel",
            FILE_STOP: "file_stop",
            FILE_ACCEPT: "file_accept",
            FILE_SAVE: "file_save",
            FILE_REJECT: "file_reject",
            FILE_OPEN: "file_open",
            FILE_OPEN_FOLDER: "file_open_folder"
        },
        

        save: function(data){
            
            var guid = system.getGuid() ;
            
            view.records[guid] = data ;
            
            view.recordMapping[data.id] = guid ;
            
            return guid ;
            
        },
        

        append: function(msg){
            
            var i, fragement = document.createDocumentFragment(), records = msg.body.records ;
            
            for(i=0; i<records.length; i++)
            {

                records[i].guid = view.save(records[i]) ;
                
                switch(records[i].type.split("-")[0])
                {
                    case "im" :
                        fragement.appendChild(im.getDOM(records[i])) ;
                        break ;
                        
                    case "sms" :
                        fragement.appendChild(sms.getDOM(records[i])) ;
                        break;
                        
                    case "file" :
                        fragement.appendChild(file.getDOM(records[i])) ;
                        break ;
                        
                    case "call" :
                        fragement.appendChild(call.getDOM(records[i])) ;
                        break ;
                        
                    case "meeting" :
                        fragement.appendChild(meeting.getDOM(records[i])) ;
                        break ;
                        
                    case "tape" :
                        fragement.appendChild(tape.getDOM(records[i])) ;
                        break ;
                }
            }
            
            view.container.appendChild(fragement) ;
            
        },
        

        prepend: function(records){
            
        },
        

        remove: function(records){
            
        }
    };
    
    function bindEvent(event)
    {
        var actionType ;
        
        event = event || window.event ;
        event.target = event.target || event.srcElement ;
        
        actionType = document.getElementById(event.target.id).actionType ;
        
        view.eventCallback[actionType](util.getId(event.target.id)) ;
    }
    

    function addEventListeners()
    {
        
        if(window.attachEvent)
        {
            view.container.attachEvent("onclick", bindEvent, false) ;
        }
        else
        {
            view.container.addEventListener("click", bindEvent, false) ;
        }
        
    }
    
    return view ;
}) ;