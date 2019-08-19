//---------------------------------------------------------------------
// <copyright file="xmlhelpers.h" company="Microsoft">
//      Copyright (C) Microsoft Corporation. All rights reserved. See License.txt in the project root for license information.
// </copyright>
//---------------------------------------------------------------------

/***
* ==++==
*
* Copyright (c) Microsoft Corporation. All rights reserved. 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* ==--==
* =+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+
*
* xmlhelpers.h
*
* This file contains xml parsing helper routines
*
* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
****/

#pragma once
#ifndef _XMLHELPERS_H
#define _XMLHELPERS_H
#ifdef WIN32
#include <atlbase.h>
#include <xmllite.h>
#else
#include <libxml/xmlreader.h>
#include <libxml/xmlwriter.h>
#include <stack>
#endif 

#include <string>
#include <vector>
#include <iostream>
#include "odata/common/basic_types.h"

namespace odata { namespace edm {

//snapper
enum XML_ELEM_TYPE
{
    XML_NODE_MODEL,
    XML_NODE_SCHEMA,
    XML_NODE_CONTAINER,
    XML_NODE_ENTITYSET,
    XML_NODE_SINGLETON,
    XML_NODE_STRUCTURE,
    XML_NODE_ENUM,
    XML_NODE_TYPEDEF,
    XML_NODE_OP,
    XML_NODE_IMPORT,
    XML_NODE_PROPTYPE,
    XML_NODE_ENUM_MEMBER,
    XML_NODE_NAVPROP_BINDING,
    XML_NODE_NAVPROP,
    XML_NODE_PARAM,
    XML_NODE_RETURNTYPE,
    XML_NODE_PROPREF,
    XML_NODE_KEY,
    XML_NODE_ANNOTATION,
    XML_NODE_EXP_RECORD,
    XML_NODE_EXP_COLLECTION,
    XML_NODE_PROPVAL,

    XML_NODE_UNKNOWN
};
class xml_elem
{
public:
    ::odata::utility::string_t name;
    XML_ELEM_TYPE type;

    virtual ~xml_elem() {}
    xml_elem()
    {
    }
    virtual void reset() {}
};

/// <summary>
/// XML reader based on xmlllite in Windows and libxml2 in other platform.
/// </summary>
class xml_reader
{
public:

    virtual ~xml_reader() {}

    /// <summary>
    /// Parse the given xml string/stream. Returns true if it finished parsing the stream to the end, and false
    /// if it was asked to exit early via pause()
    /// </summary>
    bool parse();

protected:

    xml_reader() : m_continueParsing(true), m_streamDone(false)
    {
    }

    xml_reader(std::istream& stream) : m_continueParsing(true), m_streamDone(false)
    {
        initialize(stream);
    }

    /// <summary>
    /// Callback for handling the start of an element.
    /// </summary>
    virtual std::shared_ptr<xml_elem> handle_begin_element(const ::odata::utility::string_t&)
    {
    }

    /// <summary>
    /// Callback for handling the element text.
    /// </summary>
    virtual void handle_element(const ::odata::utility::string_t& )
    {
    }

    /// <summary>
    /// Callback for handling the end of an element.
    /// </summary>
    virtual void handle_end_element(const ::odata::utility::string_t& )
    {
    }

    /// <summary>
    /// Logs an error from processing XML
    /// </summary>
    virtual void log_error_message(const std::string& message, unsigned long error = 0)
    {
        UNREFERENCED_PARAMETER(message);
        UNREFERENCED_PARAMETER(error);
    }

    /// <summary>
    /// Returns the parent element name
    /// </summary>
    ::odata::utility::string_t get_parent_element_name(size_t pos = 0);

    std::shared_ptr<xml_elem> get_parent_element(size_t pos = 0);
    std::shared_ptr<xml_elem> get_last_element();

    /// <summary>
    /// Returns the current element name
    /// </summary>
    ::odata::utility::string_t get_current_element_name();

    /// <summary>
    /// Returns the current element name with the prefix if any. 
    /// </summary>
    ::odata::utility::string_t get_current_element_name_with_prefix();

    /// <summary>
    /// Returns the current element value
    /// </summary>
    ::odata::utility::string_t get_current_element_text();

    /// <summary>
    /// Moves to the first attribute in the node
    /// </summary>
    bool move_to_first_attribute();

    /// <summary>
    /// Moves to the first attribute in the node
    /// </summary>
    bool move_to_next_attribute();

    /// <summary>
    /// Extracts the current element value into the provided type
    /// </summary>
    template <class T>
    void extract_current_element(T& value)
    {
        ::odata::utility::istringstream_t iss(get_current_element_text());
        iss >> value;
    }

    /// <summary>
    /// Initialize the reader
    /// </summary>
    ODATACPP_API void initialize(std::istream& stream);

    /// <summary>
    /// Remove Byte Order Mark from the stream
    /// </summary>
    void remove_bom(std::istream& stream);

    /// <summary>
    /// Can be called by the derived classes in the handle_* routines, to cause the parse routine to exit early,
    /// in order to capture records as they are parsed. Parsing is resumed by invoking the parse method again.
    /// </summary>
    void pause() { m_continueParsing = false; }
    
    /// <summary>
    /// Read to the end of the input stream and save the text to a string.
    /// </summary>
    ::odata::utility::string_t read_to_end(std::istream& stream);

#ifdef WIN32
    CComPtr<IXmlReader> m_reader;
#else
    xmlTextReaderPtr m_reader;
    std::string m_data;
#endif 

    std::vector<std::shared_ptr<xml_elem>> m_elementStack;
    bool m_continueParsing;
    bool m_streamDone;
};

/// <summary>
/// XML writer based on xmlllite in Windows and libxml2 in non-Windows
/// </summary>
class xml_writer
{
public:

    virtual ~xml_writer() {}

protected:
    xml_writer()
    {
    }

    /// <summary>
    /// Initialize the writer
    /// </summary>
    ODATACPP_API void initialize(std::ostream& stream);

    /// <summary>
    /// Finalize the writer
    /// </summary>
    void finalize();

    /// <summary>
    /// Write the start element tag
    /// </summary>
    void write_start_element(const ::odata::utility::string_t& elementName, const ::odata::utility::string_t& namespaceName = U(""));

    /// <summary>
    /// Writes the start element tag with a prefix
    /// </summary>
    void write_start_element_with_prefix(const ::odata::utility::string_t& elementPrefix, const ::odata::utility::string_t& elementName,
                                         const ::odata::utility::string_t& namespaceName = U(""));

    /// <summary>
    /// Write the end element tag for the current element
    /// </summary>
    void write_end_element();

    /// <summary>
    /// Write the full end element tag for the current element
    /// </summary>
    void write_full_end_element();

    /// <summary>
    /// Write an element including the name and text.
    /// </summary>
    template<class T>
    void write_element(const ::odata::utility::string_t& elementName, T value)
    {
        write_element(elementName, convert_to_string(value));
    }

    /// <summary>
    /// Write an element including the name and text.
    /// </summary>
    void write_element(const ::odata::utility::string_t& elementName, const ::odata::utility::string_t& value);

    /// <summary>
    /// Write an element including the prefix, name and text.
    /// </summary>
    void write_element_with_prefix(const ::odata::utility::string_t& prefix, const ::odata::utility::string_t& elementName, const ::odata::utility::string_t& value);

    /// <summary>
    /// Write raw data
    /// </summary>
    void write_raw(const ::odata::utility::string_t& data);

    /// <summary>
    /// Write a string
    /// </summary>
    void write_string(const ::odata::utility::string_t& string);

    /// <summary>
    /// Write an attribute string with a prefix
    /// </summary>
    void write_attribute_string(const ::odata::utility::string_t& prefix, const ::odata::utility::string_t& name,
                                const ::odata::utility::string_t& namespaceUri, const ::odata::utility::string_t& value);


    /// <summary>
    /// Logs an error from processing XML
    /// </summary>
    virtual void log_error_message(const std::string& message, unsigned long error = 0)
    {
        UNREFERENCED_PARAMETER(message);
        UNREFERENCED_PARAMETER(error);
    }
private:
#ifdef WIN32
    CComPtr<IXmlWriter> m_writer;
#else // LINUX
    xmlTextWriterPtr m_writer;
    xmlDocPtr m_doc;
    std::ostream * m_stream;
#endif
};

}} // namespace odata::edm

#endif
