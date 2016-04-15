
define(["util/util",
        "convrecord/im",
        "convrecord/sms",
        "convrecord/file",
        "convrecord/call",
        "convrecord/meeting",
        "convrecord/record",
        "convrecord/prompt",
        "component/scrollbar",
        "service/system"], 
        function(util,
                 im,
                 sms,
                 file,
                 call,
                 meeting,
                 record,
                 prompt,
                 scrollbar,
                 system){
    
    var control = {

        init: function(options){
            
            this.container = document.getElementById("im-container") ;
            
            this.eventCallback = options.eventCallback ;
            
            addEventListeners() ;
            
        },
        

        container: null,
        

        state: {
            FILE_RECEIVE_WAIT         : "file-receive-wait",              
            FILE_RECEIVE_REJECT       : "file-receive-reject",            
            FILE_RECEIVE_RECEIVER_STOP: "file-receive-receiver-stop",     
            FILE_RECEIVE_CANCEL       : "file-receive-cancel",            
            FILE_RECEIVE_SENDER_STOP  : "file-receive-sender-stop",       
            FILE_RECEIVE_PROGRESS     : "file-receive-progress",          
            FILE_RECEIVE_SUCCESS      : "file-receive-success",           
            FILE_RECEIVE_ERROR        : "file-receive-error",            
            
            FILE_SEND_WAIT            : "file-send-wait",                 
            FILE_SEND_REJECT          : "file-send-reject",               
            FILE_SEND_RECEIVER_STOP   : "file-send-receiver-stop",        
            FILE_SEND_CANCEL          : "file-send-cancel",               
            FILE_SEND_SENDER_STOP     : "file-send-sender-stop",          
            FILE_SEND_PROGRESS        : "file-send-progress",            
            FILE_SEND_SUCCESS         : "file-send-success",              
            FILE_SEND_ERROR           : "file-send-error",              
            
            SMS_SENDING     : "sms-sending",    
            SMS_SUCCESS     : "sms-success",    
            SMS_READ        : "sms-read",       
            SMS_ERROR       : "sms-error"       
        },
        

        records: {},
        

        defaultPreRecord: {
            account: "",
            time: "1900-1-1 00:00:00"
        },
        

        preRecord: {
            account: "",
            time: "1900-1-1 00:00:00"
        },
        

        excludeRecord: {
            "meeting-member-existed" : "",
            "prompt" : ""
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
            
            var guid = system.getGuid(), 

            id = data.sessionId ? data.sessionId : data.id ;
            
            data.state = data.type ;
            
            control.records[guid] = data ;
            
            control.recordMapping[id] = guid ;
            
            return guid ;
            
        },
        

        append: function(msg){
            
            var html = document.getElementsByTagName("html")[0] ;
            var isAtBottom = html.scrollTop < ( html.scrollHeight - html.clientHeight ) ? false : true ;
            var add = this.add(msg.body.records) ;
            
            control.container.appendChild( add.fragement ) ;
            

            if(system.getInfo().customScrollbar)
            {
                scrollbar.onBrowserResize() ;
            }

            else if( system.getInfo().isIE6 
                        && html.scrollHeight > html.offsetHeight)
            {
                document.getElementById("im-container").style.paddingRight = "15px" ;
            }
            
            this.toBottom(add.fromSelf, isAtBottom) ;
            
            this.clearSelection();
            
            return isAtBottom ;
        },
        
  
        prepend: function(msg){
            

            var initScrollTop = scrollbar.scrollArea.scrollTop ;
            var initScrollHeight = scrollbar.scrollArea.scrollHeight ;
            
            this.preRecord = this.defaultPreRecord ;
            
            control.container.insertBefore( this.add(msg.body.records).fragement, control.container.firstChild ) ;
            

            if(system.getInfo().customScrollbar)
            {
                scrollbar.onBrowserResize() ;
                scrollbar.scrollArea.scrollTop = parseInt(initScrollTop) + (parseInt(scrollbar.scrollArea.scrollHeight) - parseInt(initScrollHeight)) ;
                
                scrollbar.onBrowserResize() ;
            }
            
            this.clearSelection() ;
            
        },
        

        add: function(records){
            
            var fragement = document.createDocumentFragment()  ;
            var fromSelf = false ;
            var selfAccount = system.getInfo().account ;
            
            for(var i=0; i<records.length; i++)
            {
                records[i].guid = control.save(records[i]) ;
                
                switch( records[i].type.split("-")[0] )
                {
                    case "im" :
                        fragement.appendChild(im.getDOM(records[i], system.joinRecord(records[i], this.preRecord))) ;
                        
                        if(!fromSelf && (selfAccount == records[i].account))
                        {
                            fromSelf = true ;
                        }
                        break ;
                        
                    case "sms" :
                        fragement.appendChild(sms.getDOM(records[i], system.joinRecord(records[i], this.preRecord))) ;
                        
                        if(!fromSelf && (selfAccount == records[i].account))
                        {
                            fromSelf = true ;
                        }
                        break;
                        
                    case "file" :
                        fragement.appendChild(file.getDOM(records[i], system.joinRecord(records[i], this.preRecord))) ;
                        
                        if(!fromSelf && (selfAccount == records[i].account))
                        {
                            fromSelf = true ;
                        }
                        break ;
                        
                    case "call" :
                        fragement.appendChild(call.getDOM(records[i])) ;
                        break ;
                        
                    case "meeting" :
                        fragement.appendChild(meeting.getDOM(records[i])) ;
                        break ;
                        
                    case "record" :
                        fragement.appendChild(record.getDOM(records[i])) ;
                        break ;
                        
                    case "prompt" :
                        fragement.appendChild(prompt.getDOM(records[i])) ;
                        break ;
                }
                

                this.preRecord =  records[i].type in this.excludeRecord ? this.defaultPreRecord : records[i] ;
            }
            
            return {
                fragement: fragement,
                fromSelf: fromSelf
            } ;
            
        },
        

        remove: function(records){
            
        },
        

        changeState: function(record){
            
            var type = record.type.split("-")[0] ;
            
            if( type == "sms" )
            {
                sms.changeState(record) ;
            }
            else if( type == "file" )
            {
                file.changeState(record) ;
            }

        },
        

        progress: function(options){
            

            file.progress(options) ;
            
        },
        

        createScrollbar: function(options){
            
            scrollbar.init(options) ;
            
            scrollbar.onBrowserResize() ;
            
        },
        

        clear: function(){
            
            control.container.innerHTML = "" ;
            control.records = {} ;
            control.recordMapping = {} ;
            
            document.getElementById("im-container").style.paddingRight = "0px" ;
            
        },
        

        toBottom: function(fromSelf, isAtBottom){
            
            if(system.getInfo().customScrollbar)
            {
                scrollbar.toBottom() ;
            }
            else
            {
                var e = document.getElementsByTagName("html")[0] ;
                var scrollGap = e.scrollHeight - e.clientHeight ;
                
                if(isAtBottom || fromSelf)
                {
                    e.scrollTop = e.scrollHeight ;
                }
                

            }
            
        },
        

        clearSelection: function(){

        }
    };
    
    function bindEvent(event)
    {
        var actionType ;
        
        event = event || window.event ;
        event.target = event.target || event.srcElement ;
        
        if(event.target.id)
        {
            actionType = document.getElementById(event.target.id).getAttribute("actionType") ;
            
            if(actionType)
            {
                control.eventCallback[actionType](util.getId(event.target.id)) ;
            }
        }
        
    }
    
    function scrollEvent()
    {
        control.eventCallback["scroll"]() ;
    }
    
    function resizeEvent()
    {
        var e = document.getElementsByTagName("html")[0] ;
        var scrollGap = e.scrollHeight - e.clientHeight ;
        
        system.getInfo().scrollbarAtBottom = (e.scrollTop == scrollGap) ;
        
        control.eventCallback["resize"]() ;
    }
    

    function addEventListeners()
    {
        var e = document.getElementsByTagName("html")[0] ;
        
        if(window.attachEvent)
        {
            e.attachEvent("onclick", bindEvent, false) ;

            window.attachEvent("onscroll", scrollEvent, false) ;
            
            window.attachEvent("onresize", resizeEvent, false) ;
        }
        else
        {
            e.addEventListener("click", bindEvent, false) ;

            window.addEventListener("scroll", scrollEvent, false) ;
            
            window.addEventListener("resize", resizeEvent, false) ;
        }
    }
    
    return control ;
    
}) ;