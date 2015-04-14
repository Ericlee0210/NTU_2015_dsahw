#include <iostream>
#include <map>
#include <vector>

#include "func.h"
//totally correct
void get(bMap & p , const uint_64 & userID, const uint_64 & adID, const uint_16 & queryID, const uint_16 & position, const uint_16 & depth)
{
	uint_64 click_sum =0;
	uint_64 impression_sum=0;
	std::cout << "********************" << std::endl;
	//std::cout << "vector size= " << p[userID][adID][queryID].size() << std::endl;
	for(unsigned int i=0; i<p[userID][adID][queryID].size(); ++i)
	{
		if(p[userID][adID][queryID][i].userID   == userID   &&
		   p[userID][adID][queryID][i].adID     == adID     &&
		   p[userID][adID][queryID][i].queryID  == queryID  &&
		   p[userID][adID][queryID][i].position == position &&
		   p[userID][adID][queryID][i].depth    == depth      )
		{
			click_sum += p[userID][adID][queryID][i].click;
			impression_sum += p[userID][adID][queryID][i].impression;
		}
	}
	std::cout << click_sum << " " << impression_sum << std::endl;	
	std::cout << "********************" << std::endl;
	return;

}
//totally correct
void clicked(bMap & p, const uint_64 & userID)
{
	std::cout << "********************" << std::endl;
	//adID query
	for( mMap::iterator outer_i = p[userID].begin(); outer_i!=p[userID].end(); outer_i++ )
	{
		//query vector
		for(sMap::iterator inner_i = outer_i->second.begin(); inner_i!=outer_i->second.end(); inner_i++)
		{
			for(ve_container::iterator it=inner_i->second.begin(); it!=inner_i->second.end(); it++)
			{
				if(it->click>=1)
				{
					std::cout << outer_i->first << " " << inner_i->first << std::endl;
					break;
				}
			}
		}
	}
	std::cout << "********************" << std::endl;
	return;
}
//totally correct
void impressed(bMap &p, const uint_64 & userID1, const uint_64 & userID2)
{
	std::cout << "********************" << std::endl;
	//判斷userID1、userID2誰的adID比較多
	if(p[userID1].size() >= p[userID2].size() ) //userID2比較少
	{
		//讀每一個adID，mi->first為adID
		for(  mMap::iterator mi =p[userID2].begin(); mi!=p[userID2].end(); mi++)
		{
			//拷貝目前的adID
			uint_64 adID_cpy = mi->first;
			//判斷這樣的adID在不在另外一個使用者身上
			if(p[userID1].find(adID_cpy) == p[userID1].end()) // 沒有出現
			{	
				//處理沒有出現，直接找下個adID in userID2
				continue;
			}
			else
			{
				//buffer
				ve_container buffer;

				//處理有出現，讀出每個queryID
				for(sMap::iterator si = p[userID2][adID_cpy].begin(); si!= p[userID2][adID_cpy].end(); si++)
				{
					//拷貝目前的queryID
					uint_16 queryID_cpy = si->first;
					//讀出vector element in one query
					for(ve_container::iterator vi = p[userID2][adID_cpy][queryID_cpy].begin(); vi!=p[userID2][adID_cpy][queryID_cpy].end(); vi++)
					{
						if(buffer.empty())
							buffer.push_back(*vi);
						else //buffer不是空的，要跟buffer裡面做比較，跟全部不一樣才放入
						{
							//比較buffer元素，不一樣才能放
							for(ve_container::iterator buffer_vi = buffer.begin(); ; buffer_vi++)
							{
								//std::cout << "problem" << std::endl;
								if(*vi==*buffer_vi)
									break;
								if(buffer_vi==buffer.end()-1)
								{
									buffer.push_back(*vi);
									break;
								}
							}
						}
					}
				}
				//std::cout << "first part" << std::endl;
				//接著，讀出另一個不同userID，adID卻相同的所有queryID
				for(sMap::iterator si = p[userID1][adID_cpy].begin(); si!=p[userID1][adID_cpy].end(); si++)
				{
					//拷貝目前queryID
					uint_16 queryID_cpy = si->first;
					//讀出所有queryID
					for(ve_container::iterator vi = p[userID1][adID_cpy][queryID_cpy].begin(); vi!=p[userID1][adID_cpy][queryID_cpy].end(); vi++)
					{
						if(buffer.empty())
							buffer.push_back(*vi);
						else //buffer不是空的，要跟之前buffer所有比
						{
							//比較buffer元素，不一樣才能放
							for(ve_container::iterator buffer_vi = buffer.begin(); ; buffer_vi++)
							{
								//std::cout << "problem" << std::endl;
								if(*vi==*buffer_vi)
									break;
								if(buffer_vi==buffer.end()-1)
								{
									buffer.push_back(*vi);
									break;
								}
							}
						}						
					}
				}
				//std::cout << "second part" << std::endl;
				printf("%llu\n", adID_cpy);
				//印出同樣adID，所有被看過的廣告的資料
				for(ve_container::iterator buffer_vi = buffer.begin(); buffer_vi!=buffer.end(); buffer_vi++)
				{	
					printf("\t%s %u %u %u %u\n", buffer_vi->displayURL, buffer_vi->advertiseID, buffer_vi->keywordID, buffer_vi->titleID, buffer_vi->descriptionID);
				}
				//std::cout << "third part" << std::endl;
			}
		}
	}
	else //userID1比較少
	{
		//讀每一個adID，mi->first為adID
		for(  mMap::iterator mi =p[userID1].begin(); mi!=p[userID1].end(); mi++)
		{
			//拷貝目前的adID
			uint_64 adID_cpy = mi->first;
			//判斷這樣的adID在不在另外一個使用者身上
			if(p[userID2].find(adID_cpy) == p[userID2].end()) // 沒有出現
			{	
				//處理沒有出現，直接找下個adID in userID1
				continue;
			}
			else
			{
				//buffer
				ve_container buffer;

				//處理有出現，讀出每個queryID
				for(sMap::iterator si = p[userID1][adID_cpy].begin(); si!= p[userID1][adID_cpy].end(); si++)
				{
					//拷貝目前的queryID
					uint_16 queryID_cpy = si->first;
					//讀出vector element in one query
					for(ve_container::iterator vi = p[userID1][adID_cpy][queryID_cpy].begin(); vi!=p[userID1][adID_cpy][queryID_cpy].end(); vi++)
					{
						if(buffer.empty())
							buffer.push_back(*vi);
						else //buffer不是空的，要跟buffer裡面做比較，跟全部不一樣才放入
						{
							//比較buffer元素，不一樣才能放
							for(ve_container::iterator buffer_vi = buffer.begin(); ; buffer_vi++)
							{
								//std::cout << "problem" << std::endl;
								if(*vi==*buffer_vi)
									break;
								if(buffer_vi==buffer.end()-1)
								{
									buffer.push_back(*vi);
									break;
								}
							}
						}
					}
				}
				//std::cout << "first part" << std::endl;
				//接著，讀出另一個不同userID，adID卻相同的所有queryID
				for(sMap::iterator si = p[userID2][adID_cpy].begin(); si!=p[userID2][adID_cpy].end(); si++)
				{
					//拷貝目前queryID
					uint_16 queryID_cpy = si->first;
					//讀出所有queryID
					for(ve_container::iterator vi = p[userID2][adID_cpy][queryID_cpy].begin(); vi!=p[userID2][adID_cpy][queryID_cpy].end(); vi++)
					{
						if(buffer.empty())
							buffer.push_back(*vi);
						else //buffer不是空的，要跟之前buffer所有比
						{
							//比較buffer元素，不一樣才能放
							for(ve_container::iterator buffer_vi = buffer.begin(); ; buffer_vi++)
							{
								//std::cout << "problem" << std::endl;
								if(*vi==*buffer_vi)
									break;
								if(buffer_vi==buffer.end()-1)
								{
									buffer.push_back(*vi);
									break;
								}
							}
						}						
					}
				}
				//std::cout << "second part" << std::endl;
				printf("%llu\n", adID_cpy);
				//印出同樣adID，所有被看過的廣告的資料
				for(ve_container::iterator buffer_vi = buffer.begin(); buffer_vi!=buffer.end(); buffer_vi++)
				{	
					printf("\t%s %u %u %u %u\n", buffer_vi->displayURL, buffer_vi->advertiseID, buffer_vi->keywordID, buffer_vi->titleID, buffer_vi->descriptionID);
				}
				//std::cout << "third part" << std::endl;
			}
		}
	}
	std::cout << "********************" << std::endl;
	return;
}


void profit(bMap & p,  const uint_16 & adID, const double & theta)
{
	std::cout << "********************" << std::endl;
	//把每個userID都讀出來
	for(bMap::iterator bi = p.begin(); bi!=p.end(); bi++)
	{
		//拷貝userID
		uint_64 userID_cpy = bi->first;

		//確認bi是否包含adID的key
		mMap::iterator mi = bi->second.find(adID);
		if( mi==bi->second.end())  //沒有adID，繼續找下個userID
			continue;
		else 
		{
			//to save total click
			double tclick = 0.0;
			//to save total impressioin
			double timpression =0.0;

			//將所有queryID拿出來
			for(sMap::iterator si = p[userID_cpy][adID].begin(); si!=p[userID_cpy][adID].end(); si++)
			{
				//拷貝queryID
				uint_16 queryID_cpy =si->first;

				//將個別vector element拿出來
				for(ve_container::iterator vi = p[userID_cpy][adID][queryID_cpy].begin(); vi != p[userID_cpy][adID][queryID_cpy].end(); vi++)
				{
					tclick += double(vi->click);
					timpression += double(vi->impression);
				}
			}

			//算出theta
			if(tclick/timpression >= theta)
			printf("%llu\n", userID_cpy);
		}
	}
	std::cout << "********************" << std::endl;
	return;
}

void quit()
{
	return;
}
