/******************************************************************************
* Huawei Enterprise Communication API
* group.h
* Author :  Huawei
* Description :  Group related API
* Create Time:  2011-7-02 16:00:00
* Copyright (c) 2012 Huawei Technologies Co., Ltd.
* All rights reserved.

* Revision History :  2011-7-02 1.00  First version
******************************************************************************/

#pragma once

namespace uc {
	namespace model {
		namespace conversation {

			/**
			* \brief Participant
			* \note The Participant class represents attendee of the Conversation
			* \author  y00135380
			* \version 1.0.0  initial version
			*/
			class APPCLASSLAYER_API Participant
			{
			public:

				Participant()
				{
					//pDataConfInfo_ = NULL;
				}

				Participant(const Participant& _part)
				{
					this->contact_ = _part.contact_;
				}

				~Participant()
				{
				}

				Participant& operator = (const Participant& par)
				{
					if (&par != this)
					{
						this->contact_ = par.contact_;
					}

					return *this;
				}

				uc::model::Contact contact_;   //!< participant detail info
			};

		}
	}
}
