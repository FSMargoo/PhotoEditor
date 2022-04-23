#pragma once

#include "seal.lexical.hpp"

#include <map>

namespace PDotE
{
	namespace UI
	{
#define PassToken token = lexical->get_token()
#define NotEof    !lexical->is_eof()
#define UnexpectTokenError node.last_error = "SyntaxError : Excpetion String \"" + token.token_string + "\"!";  return node;
#define CheckPositon (lexical->get_index() < file_content.size())
#define CheckString if (token.cache_token != UNKNOW_TOKEN) { node.last_error = "SyntaxError : Excpetion String \"" + token.token_string + "\"!";  return node; }
#define CheckStringEqual if (token.token_string != "=") { node.last_error = "SyntaxError : Excpetion String \"" + token.token_string + "\", it sould be \"=\"!";  return node; }
#define CheckEnd		 if (token.token_string != ">") { node.last_error = "SyntaxError : Excpetion String \"" + token.token_string + "\"!";  return node; }
#define CheckStart		 if (token.token_string != "<") { node.last_error = "SyntaxError : Excpetion String \"" + token.token_string + "\"!";  return node; }
#define CheckNode(n) if (##n.IsUsefulNode() == false) node.last_error = ##n.last_error
		
		struct XmlProperty
		{
			std::string  value_as_string;
			bool		 value_as_boolean = false;
			long long	 value_as_number  = 0;

			short		 property_type	  = 0;
		};

		struct _XmlNode
		{
			std::string						   node_name;
			
			XmlProperty						   node_content;

			std::map<std::string, XmlProperty> propertys;
			std::map<int, _XmlNode*>   child_object;

			bool IsProperty(std::string keyName)
			{
				return propertys.find(keyName) != propertys.end();
			}
			_XmlNode* operator[](std::string keyName)
			{
				_XmlNode* temp = new _XmlNode;

				for (auto& item : child_object)
				{
					if (item.second->node_name == keyName)
					{
						*(temp) = *(item.second);

						return temp;
					}
				}

				return nullptr;
			}
			_XmlNode* operator[](const char* keyName)
			{
				_XmlNode* temp = new _XmlNode;

				for (auto& item : child_object)
				{
					if (item.second->node_name == keyName)
					{
						*(temp) = *(item.second);

						return temp;
					}
				}

				return nullptr;
			}
		};

		struct XmlNode
		{
			std::string  last_error;
			std::map<int, _XmlNode*> child_object;

			bool IsUsefulNode()
			{
				return last_error.empty();
			}
			_XmlNode* operator[](std::string keyName)
			{
				_XmlNode* temp = new _XmlNode;

				for (auto& item : child_object)
				{
					if (item.second->node_name == keyName)
					{
						*(temp) = *(item.second);

						return temp;
					}
				}

				return nullptr;
			}

			_XmlNode ToNode()
			{
				_XmlNode result;

				result.child_object = child_object;

				return result;
			}
		};

		class  XmlParser
		{
		private:
			std::string file_content;

		public:
			XmlParser(std::string content)
			{
				file_content = content;
			}

			XmlNode Parse()
			{
				XmlNode		  node;
				_XmlNode      temp_node;

				seal_lexcial* lexical = new seal_lexcial(file_content);
				auto		  PassToken;

				int			  temp_position = 0;

				while (NotEof)
				{
					temp_node.child_object.clear();
					temp_node.propertys.clear();

					if (token.token_string == "<")
					{
						PassToken;

						if (token.token_string == "?" ||
							token.token_string == "!")
						{
							while (NotEof)
							{
								PassToken;

								if (token.token_string == ">")
								{
									break;
								}
							}

							if (!CheckPositon)
							{
								node.last_error = "SyntaxError : Lose \'>\'!";

								return node;
							}

							continue;
						}

						auto node_name = token.token_string;

						temp_node.node_name = node_name;

						bool flag = false;

						CheckString;

						{
							std::string p_name;

							XmlProperty temp_property;

							{
								while (NotEof)
								{
									PassToken;

									if (token.token_string == ">")
									{
										flag = true;

										break;
									}

									p_name = token.token_string;

									PassToken;

									CheckStringEqual;

									PassToken;

									{
										if (token.cache_token == CONST_NUMBER)
										{
											temp_property.property_type = 0;

											temp_property.value_as_number = _atoi64(token.token_string.c_str());
										}
										else if (token.cache_token == CONST_STRING)
										{
											temp_property.property_type = 1;

											temp_property.value_as_string = token.token_string.substr(1, token.token_string.size() - 2);
										}
										else if (token.cache_token == CONST_BOOLEAN)
										{
											temp_property.property_type = 2;

											if (token.token_string == "false")
											{
												temp_property.value_as_boolean = false;
											}
											if (token.token_string == "true")
											{
												temp_property.value_as_boolean = true;
											}
										}
										else
										{
											UnexpectTokenError;
										}

										temp_node.propertys.insert(std::pair<std::string, XmlProperty>(p_name, temp_property));
									}
								}

								if (flag == false)
								{
									node.last_error = "SyntaxError : Lose \'>\'!";

									return node;
								}
							}

							PassToken;

							std::string temp_content;

							{
								if (token.token_string == "<")
								{
									temp_property.property_type = 3;

									std::string child_content = "<";
									int         level = 0;

									flag = false;

									while (NotEof)
									{
										PassToken;

										if (token.token_string == "<")
										{
											temp_content += token.token_string;

											PassToken;

											if (token.token_string == node_name)
											{
												++level;
											}

											temp_content += token.token_string;

											if (token.token_string == "/")
											{
												PassToken;

												temp_content += token.token_string;

												if (token.token_string == node_name)
												{
													if (level != 0)
													{
														--level;

														PassToken;

														if (token.token_string != ">") { UnexpectTokenError }

														child_content += temp_content + "> ";

														temp_content.clear();

														continue;
													}

													PassToken;

													flag = true;

													if (token.token_string != ">") { UnexpectTokenError }

													break;
												}
											}

											child_content += temp_content + " ";

											temp_content.clear();

											continue;
										}

										child_content += token.token_string + " ";
									}

									if (flag == false)
									{
										node.last_error = "SyntaxError : Lose \'>\'!";

										return node;
									}

									XmlParser* parser = new XmlParser(child_content);

									auto result = parser->Parse();

									CheckNode(result);

									for (auto& item : result.child_object)
									{
										temp_node.child_object.insert(item);
									}

									node.child_object.insert(std::pair<int, _XmlNode*>(temp_position, new _XmlNode(temp_node)));

									++temp_position;

									continue;
								}
								else if (token.cache_token == CONST_NUMBER)
								{
									temp_property.property_type = 0;

									temp_property.value_as_number = _atoi64(token.token_string.c_str());
								}
								else if (token.cache_token == CONST_STRING)
								{
									temp_property.property_type = 1;

									temp_property.value_as_string = token.token_string.substr(1, token.token_string.size() - 2);
								}
								else if (token.cache_token == CONST_BOOLEAN)
								{
									temp_property.property_type = 2;

									if (token.token_string == "false")
									{
										temp_property.value_as_boolean = false;
									}
									if (token.token_string == "true")
									{
										temp_property.value_as_boolean = true;
									}
								}
								else if (token.token_string == "RGB")
								{
									PassToken;
									PassToken;
									int r = _atoi64(token.token_string.c_str());
									PassToken;

									PassToken;
									int g = _atoi64(token.token_string.c_str());
									PassToken;

									PassToken;
									int b = _atoi64(token.token_string.c_str());
									PassToken;

									temp_property.property_type = 0;


									temp_property.value_as_number = RGB(r, g, b);
								}
								else
								{
									UnexpectTokenError;
								}

								temp_node.node_content = temp_property;

								{
									PassToken;
									CheckStart;
									PassToken;

									if (token.token_string != "/")
									{
										UnexpectTokenError;
									}

									PassToken;

									if (token.token_string != node_name)
									{
										UnexpectTokenError;
									}

									PassToken;

									CheckEnd;

									node.child_object.insert(std::pair<int, _XmlNode*>(temp_position, new _XmlNode(temp_node)));

									++temp_position;
								}
							}
						}
					}

					PassToken;
				} 

				return node;
			}
		};
	}
}
