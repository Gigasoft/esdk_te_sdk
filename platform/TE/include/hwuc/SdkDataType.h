#pragma once

namespace ecs
{
    namespace sdk
    {
        namespace basic
        {
            //��ϵ����ϸ��Ϣ
            class Contact
            {
            public:
                std::string id_;            //!< id
                std::string uri_;           //!< sip uri
                std::string ucNo_;          //!< �˺�
                std::string workNo_;        //!< ����
                std::string name_;          //!< ����
                std::string nickName_;      //!< �ǳƣ�������չ
                
#ifdef __APPLE__
                std::string qpinyin_;   //!< name fullpinyin
                std::string spinyin_;   //!< name simplepinyin
#endif
                
                
                std::string homePhone_;     //!< ��ͥ�绰��������չ
                std::string officePhone_;   //!< �칫�ҵ绰��������չ
                std::string mobile_;        //!< �ֻ�����
                std::string otherPhone_;    //!< �����绰
                std::string address_;       //!< ��ϵ��ַ
                std::string email_;         //!< email
                std::string career_;	    //!< ְλ
                std::string fax_;           //����
                std::string gender_;        //�Ա�
                std::string corpName_;      //!< ��ҵ��
                std::string deptName_;      //!< ������
                std::string webSite_;       //!< ������վ
                std::string desc_;          //!< ����
                std::string zip_;           //!< �ʱ�
                std::string terminalType_;  //��ϵ������
                
                Contact()
                {
					id_ = "";
					uri_ = "";           //!< sip uri
					ucNo_ = "";          //!< �˺�
					workNo_ = "";        //!< ����
					name_ = "";          //!< ����
					nickName_ = "";      //!< �ǳƣ�������չ
                    
#ifdef __APPLE__
                    qpinyin_ = "";
                    spinyin_ = "";
#endif
                    
					homePhone_ = "";     //!< ��ͥ�绰��������չ
					officePhone_ = "";   //!< �칫�ҵ绰��������չ
					mobile_ = "";        //!< �ֻ�����
					otherPhone_ = "";    //!< �����绰
					address_ = "";       //!< ��ϵ��ַ
					email_ = "";         //!< email
					career_ = "";	    //!< ְλ
					fax_ = "";           //����
					gender_ = "";        //�Ա�
					corpName_ = "";      //!< ��ҵ��
					deptName_ = "";      //!< ������
					webSite_ = "";       //!< ������վ
					desc_ = "";          //!< ����
					zip_ = "";           //!< �ʱ�
					terminalType_ = "";  //��ϵ������
                }
            };

            //ͨ��¼���˷�����Ϣ
            class UserGroup
            {
            public:
                std::string groupId_;   //!< ��ID
        	    std::string groupName_; //!< ����
                std::string state_;     //!< ״̬
                std::string index_;     //!< ������ʾ���, ��������չ
                
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


