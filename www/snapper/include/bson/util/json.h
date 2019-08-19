/*    Copyright 2009 10gen Inc.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */


#pragma once

#include "../bson.h"

namespace bson {

    /** Create a BSONObj from a JSON <http://www.json.org> string.  In addition
     to the JSON extensions extensions described here
     <http://mongodb.onconfluence.com/display/DOCS/Mongo+Extended+JSON>,
     this function accepts certain unquoted field names and allows single quotes
     to optionally be used when specifying field names and string values instead
     of double quotes.  JSON unicode escape sequences (of the form \uXXXX) are
     converted to utf8.
     \throws MsgAssertionException if parsing fails.  The message included with
     this assertion includes a rough indication of where parsing failed.
    */
    BSONObj fromjson(const string &str);

    /** len will be size of JSON object in text chars. */
    BSONObj fromjson(const char *str, int* len=NULL);

} // namespace mongo
