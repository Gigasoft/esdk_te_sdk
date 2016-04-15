
define(["convrecord/control",
        "service/system",
        "util/util"], 
        function(control,
                 system,
                 util){
    

    io = {
        
        init: function(){
            
            control.init({
                eventCallback: eventCallback
            }) ;

        },

        receive: function(msg){

            return ioCallback[msg.type](msg) ;
            
        },
        

        send: function(msg){
            
				return window.external.receive(msg) ;
            
        },
        

        msgType: {
            INIT    : "init",         
            APPEND  : "append",       
            PREPEND : "prepend",
            
            SMS_SENDING : "sms-sending",
            SMS_SUCCESS : "sms-success",
            SMS_ERROR   : "sms-error",
            SMS_READ    : "sms-read",
            SMS_RECEIVE : "sms-receive",
            
            FILE_RECEIVE_REJECT        : "file-receive-reject",
            FILE_RECEIVE_RECEIVER_STOP : "file-receive-receiver-stop",
            FILE_RECEIVE_CANCEL        : "file-receive-cancel",
            FILE_RECEIVE_SENDER_STOP   : "file-receive-sender-stop",
            FILE_RECEIVE_PROGRESS      : "file-receive-progress",
            FILE_RECEIVE_SUCCESS       : "file-receive-success",
            FILE_RECEIVE_ERROR         : "file-receive-error",
            FILE_RECEIVE_NOT_EXIST     : "file-receive-not-exist",

            FILE_SEND_WAIT             : "file-send-wait",
            FILE_SEND_REJECT           : "file-send-reject",
            FILE_SEND_RECEIVER_STOP    : "file-send-receiver-stop",
            FILE_SEND_CANCEL           : "file-send-cancel",
            FILE_SEND_SENDER_STOP      : "file-send-sender-stop",
            FILE_SEND_PROGRESS         : "file-send-progress",
            FILE_SEND_SUCCESS          : "file-send-success",
            FILE_SEND_ERROR            : "file-send-error",
            FILE_SEND_TOO_LARGE        : "file-send-too-large",
            FILE_SEND_FAILED           : "file-send-failed",
            FILE_SEND_NO_PERMISSION    : "file-send-no-permission",
            
            FILE_SPACE_NOT_ENOUGH      : "file-space-not-enough",
            
            MEETING_MEMBER_ENTER : "meeting-member-enter",
            MEETING_MEMNER_LEAVE : "meeting-member-leave",
            MEETING_SELF_LEAVE   : "meeting-self-leave",
            
            RECORD_OPEN: "record-open",
            
            CLEAR: "clear",
            
            SCROLLBAR_TO_BOTTOM: "scrollbar-to-bottom",
            
            GET_FIRST_RECORD: "get-first-record"
        }
    };
    
    var ioCallback = {}, eventCallback = {} ;
    

    ioCallback[io.msgType.INIT] = function(msg){
        
        system.init(msg.body) ;
        

        if(msg.body.hasHistory)
        {
            var dom = document.createElement("div") ;
            
            dom.className = "load-more" ;
            dom.id = "load-more" ;
            dom.innerHTML = '<span id="load-more-text" actionType="load-more" class="load-more-text">{loadMore}</span>'.replace(/{loadMore}/g, system.getLang().LOAD_MORE) ;
            
            document.getElementsByTagName("body")[0].insertBefore(dom, control.container) ;
        }
        

        if(msg.body.customScrollbar)
        {
            control.createScrollbar({
                scrollArea: document.getElementById("im-container"),
                container: document.getElementsByTagName("body")[0]
            }) ;
        }

        else
        {

            var html = document.getElementsByTagName("html")[0] ;
            
            html.style.overflowX = "hidden" ;
            html.style.overflowY = "auto" ;
        }
        
    } ;

    ioCallback[io.msgType.APPEND] = function(msg){
        
        var isAtBottom = control.append(msg) ;
        
        io.send("<root __type__=\"srollbar-at-bottom\"><position>" + isAtBottom + "</position></root>") ;
        
    } ;
    

    ioCallback[io.msgType.PREPEND] = function(msg){
        
        control.prepend(msg) ;
        
    } ;
    

    ioCallback[io.msgType.SMS_SENDING] = function(msg){
        
        msg.body.id = control.recordMapping[msg.body.sessionId] ;
        msg.type = io.msgType.SMS_SENDING ;
		
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.SMS_SUCCESS] = function(msg){
        
        msg.body.id = control.recordMapping[msg.body.sessionId] ;
        msg.type = io.msgType.SMS_SUCCESS ;
		
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.SMS_ERROR] = function(msg){
        
        msg.body.id = control.recordMapping[msg.body.sessionId] ;
        msg.type = io.msgType.SMS_ERROR ;
		
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.SMS_READ] = function(msg){
        
        msg.body.id = control.recordMapping[msg.body.sessionId] ;
        msg.type = io.msgType.SMS_READ ;
		
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.SMS_RECEIVE] = function(msg){
        
        msg.body.id = control.recordMapping[msg.body.sessionId] ;
        msg.type = io.msgType.SMS_RECEIVE ;
		
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_RECEIVE_CANCEL] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_CANCEL ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_RECEIVE_ERROR] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_ERROR ;
        
        control.changeState(msg) ;
        
    } ;
	

    ioCallback[io.msgType.FILE_SEND_TOO_LARGE] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_TOO_LARGE ;
		
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_RECEIVE_PROGRESS] = function(msg){
        
        var record = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        
        util.extend(record, msg.body) ;
        

        if(record.type.indexOf("progress") == -1)
        {
            record.type = control.state.FILE_RECEIVE_PROGRESS ;
            control.changeState(record) ;
        }
        
        control.progress(record) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_RECEIVE_RECEIVER_STOP] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_RECEIVER_STOP ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_RECEIVE_REJECT] = function(msg){
        
		alert(msg.body.sessionId) ;
		
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_REJECT ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_RECEIVE_SENDER_STOP] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_SENDER_STOP ;
        
        control.changeState(msg) ;
        
    } ;

    ioCallback[io.msgType.FILE_RECEIVE_SUCCESS] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_SUCCESS ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_CANCEL] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_CANCEL ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_ERROR] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_ERROR ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_PROGRESS] = function(msg){
        
        var record = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        
        util.extend(record, msg.body) ;
        

        if(record.type.indexOf("progress") == -1)
        {
            record.type = control.state.FILE_SEND_PROGRESS ;
            control.changeState(record) ;
        }
        
        control.progress(record) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_RECEIVER_STOP] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_RECEIVER_STOP ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_REJECT] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_REJECT ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_SENDER_STOP] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_SENDER_STOP ;
        
        control.changeState(msg) ;
        
    } ;

    ioCallback[io.msgType.FILE_SEND_SUCCESS] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_SUCCESS ;
        
        control.changeState(msg) ;
        
    } ;
	

    ioCallback[io.msgType.FILE_RECEIVE_NOT_EXIST] = function(msg){
        
		msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_RECEIVE_NOT_EXIST ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SPACE_NOT_ENOUGH] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SPACE_NOT_ENOUGH ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_FAILED] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_FAILED ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.FILE_SEND_NO_PERMISSION] = function(msg){
        
        msg = control.records[ control.recordMapping[msg.body.sessionId] ] ;
        msg.type = io.msgType.FILE_SEND_NO_PERMISSION ;
        
        control.changeState(msg) ;
        
    } ;
    

    ioCallback[io.msgType.CLEAR] = function(msg){
        
        control.clear() ;
        
    } ;
    

    ioCallback[io.msgType.SCROLLBAR_TO_BOTTOM] = function(msg){
        
        control.toBottom(msg.body.toBottom) ;
        
    } ;
    

    ioCallback[io.msgType.GET_FIRST_RECORD] = function(msg){
        
        return control.getFirstRecord() ;
        
    } ;
    

    eventCallback["sms-send-again"] = function(id){
        

        control.changeState({
            type: control.state.SMS_SENDING,
            body: {
                id: id
            }
        }) ;
        

       io.send("<root __type__=\"sms-send-again\"><session-id>" + control.records[id].sessionId + "</session-id></root>") ;
        
    } ;
    

    eventCallback["file-stop"] = function(id){
        
        var record = control.records[id] ;
        

        if( record.account == system.getInfo().account )
        {
            record.type == "file-send-wait" ? record.type = control.state.FILE_SEND_CANCEL : record.type = control.state.FILE_SEND_SENDER_STOP ;
            
            control.changeState(record) ;
        }

        else
        {
            record.type = control.state.FILE_RECEIVE_RECEIVER_STOP ;
            
            control.changeState(record) ;
        }
        
        io.send("<root __type__=\"file-stop\"><session-id>" + control.records[id].sessionId + "</session-id></root>") ;
        
    } ;
    

    eventCallback["file-accept"] = function(id){
        
        io.send("<root __type__=\"file-accept\"><session-id>" + control.records[id].sessionId + "</session-id><id>" + control.records[id].id + "</id></root>") ;

        
    } ;

    eventCallback["file-save"] = function(id){
        
        io.send("<root __type__=\"file-save\"><session-id>" + control.records[id].sessionId + "</session-id></root>") ;
        
    } ;
    

    eventCallback["file-reject"] = function(id){
        
       var record = control.records[id] ;
	   var result = 0 ;
        
       record.type = control.state.FILE_RECEIVE_REJECT ;
        
       result = io.send("<root __type__=\"file-reject\"><session-id>" + control.records[id].sessionId + "</session-id></root>") ;

       result==1 ? control.changeState(record) : "" ;
        
    } ;
    

    eventCallback["file-open"] = function(id){
        
        io.send("<root __type__=\"file-open\"><id>" + control.records[id].id + "</id></root>") ;
        
    } ;
    

    eventCallback["file-open-folder"] = function(id){
        
        io.send("<root __type__=\"file-open-folder\"><id>" + control.records[id].id + "</id></root>") ;
        
    } ;
    

    eventCallback["file-send-again"] = function(id){
        
        var newId ;
        var record = control.records[id] ;
        
        record.type = control.state.FILE_SEND_WAIT ;
        
        control.changeState(record) ;
        

        newId = io.send("<root __type__=\"file-send-again\"><session-id>" + control.records[id].sessionId + "</session-id></root>") ;
        
        delete control.recordMapping[control.records[id].sessionId] ;
        
        control.records[id].sessionId = newId ;
        control.recordMapping[newId] = id ;
        
    } ;

    eventCallback["record-open"] = function(id){
        
        io.send("<root __type__=\"record-open\"><id>" + control.records[id].id + "</id><file-url>" + control.records[id].filePath + "</file-url></root>") ;
        
    } ;
    

    eventCallback["show-context"] = function(id){
        
        io.send("<root __type__=\"show-context\"><id>" + control.records[id].id + "</id></root>") ;
        
    } ;
    

    eventCallback["load-more"] = function(id){
        
        var id = control.getFirstRecord().id ;
        
        io.send("<root __type__=\"load-more\"><id>" + id ? id : "" + "</id></root>") ;
        
    } ;
    

    eventCallback["scroll"] = function(id){
        
        var e = document.getElementsByTagName("html")[0] ;
        var scrollGap = e.scrollHeight - e.clientHeight ;
        
        if(e.scrollTop == scrollGap)
        {
            io.send("<root __type__=\"srollbar-at-bottom\"><position>" + (e.scrollTop == scrollGap) + "</position></root>") ;
        }
        
        system.getInfo().scrollbarAtBottom = (e.scrollTop == scrollGap) ;
        
    } ;
    
    eventCallback["resize"] = function(){
        
        var e = document.getElementsByTagName("html")[0] ;
        var scrollGap = e.scrollHeight - e.clientHeight ;
        
        if(system.getInfo().scrollbarAtBottom)
        {
            e.scrollTop = scrollGap ;
        }
        
    } ;
    
    return io ;
    
}) ;