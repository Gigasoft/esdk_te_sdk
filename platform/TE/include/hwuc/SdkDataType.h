#pragma once

namespace ecs
{
    namespace sdk
    {
        namespace basic
        {
            //联系人详细信息
            class Contact
            {
            public:
                std::string id_;            //!< id
                std::string uri_;           //!< sip uri
                std::string ucNo_;          //!< 账号
                std::string workNo_;        //!< 工号
                std::string name_;          //!< 姓名
                std::string nickName_;      //!< 昵称，保留扩展
                
#ifdef __APPLE__
                std::string qpinyin_;   //!< name fullpinyin
                std::string spinyin_;   //!< name simplepinyin
#endif
                
                
                std::string homePhone_;     //!< 家庭电话，保留扩展
                std::string officePhone_;   //!< 办公室电话，保留扩展
                std::string mobile_;        //!< 手机号码
                std::string otherPhone_;    //!< 其他电话
                std::string address_;       //!< 联系地址
                std::string email_;         //!< email
                std::string career_;	    //!< 职位
                std::string fax_;           //传真
                std::string gender_;        //性别
                std::string corpName_;      //!< 企业名
                std::string deptName_;      //!< 部门名
                std::string webSite_;       //!< 个人网站
                std::string desc_;          //!< 描述
                std::string zip_;           //!< 邮编
                std::string terminalType_;  //联系人类型
                
                Contact()
                {
					id_ = "";
					uri_ = "";           //!< sip uri
					ucNo_ = "";          //!< 账号
					workNo_ = "";        //!< 工号
					name_ = "";          //!< 姓名
					nickName_ = "";      //!< 昵称，保留扩展
                    
#ifdef __APPLE__
                    qpinyin_ = "";
                    spinyin_ = "";
#endif
                    
					homePhone_ = "";     //!< 家庭电话，保留扩展
					officePhone_ = "";   //!< 办公室电话，保留扩展
					mobile_ = "";        //!< 手机号码
					otherPhone_ = "";    //!< 其他电话
					address_ = "";       //!< 联系地址
					email_ = "";         //!< email
					career_ = "";	    //!< 职位
					fax_ = "";           //传真
					gender_ = "";        //性别
					corpName_ = "";      //!< 企业名
					deptName_ = "";      //!< 部门名
					webSite_ = "";       //!< 个人网站
					desc_ = "";          //!< 描述
					zip_ = "";           //!< 邮编
					terminalType_ = "";  //联系人类型
                }
            };

            //通信录个人分组信息
            class UserGroup
            {
            public:
                std::string groupId_;   //!< 组ID
        	    std::string groupName_; //!< 组名
                std::string state_;     //!< 状态
                std::string index_;     //!< 分组显示序号, 保留待扩展
                
                UserGroup()
                {
                    groupId_ = "";
                    groupName_ = "";
                    state_ = "";
                    index_ = "";
                }
            };

        } // end of namespace basic
    } // end of namespace sdk
} // end of namespace ecs


