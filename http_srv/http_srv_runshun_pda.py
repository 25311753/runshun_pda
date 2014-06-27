#!/usr/bin/python
# -*- coding: gb2312 -*- 

import sys
reload(sys)
sys.setdefaultencoding( "utf-8" )
from bottle import Bottle,route, run,template,static_file,request,abort,get,put,post,response,HTTPError
import pymssql
import traceback
import datetime

DB_HOST='124.173.70.227'
DB_PORT=36928
DB_USER='runshunuser'
DB_PW='runshunuser'
DB_AUTOCOMMIT=True
DB_AS_DICT=True
DB='runshun'

CONN = None

def get_connection():
    print 'init get connection'
    conn = None
    try:
        if (hasattr(conn, 'close')):
            conn.close()
        conn = pymssql.connect(host=DB_HOST, port=DB_PORT, user=DB_USER, password=DB_PW, database=DB, as_dict=DB_AS_DICT)
        conn.autocommit(DB_AUTOCOMMIT)
        print 'conn ok'
    except Exception as e:
        print e
        conn = None

    print id(conn)
    return conn

CONN=get_connection()
print id(CONN)

@get('/change_status')
def change_status():
    print '------------------change_status---------------------'
    global CONN
    new_status = request.query.new_status
    cid = request.query.cid

    if not new_status or not cid:
        abort(400, 'bad requests')

    print 'cid:%s new_status:%s'%(cid, new_status)
    
    cur = None
    try:
        cur = CONN.cursor()
        #check exist first
        cur.execute('select cid from customs where cid=%s', cid)
        row = cur.fetchone()
        if not row:
            print 'cid not exist'
            return HTTPError(404, 'not exists')
        str_pass_date = datetime.datetime.now().strftime('%Y-%m-%d %H:%M')
        if new_status=='0':
            new_status=u"已放行"
            sql = "update customs set status='%s', pass_date='%s' where cid=%s"%(new_status, str_pass_date, cid)
        else:            
            new_status=u"已交放行条"
            #fix mod by pad but pass_data not chang 20140627
            sql = "update customs set status='%s', pass_date=(case when pass_date is NULL then '%s' when pass_date='-' then '%s' else pass_date end) where cid=%s"%(new_status, str_pass_date, str_pass_date, cid)    
        cur.execute(sql)
    except Exception as e:
        print e
        if (hasattr(CONN,'close')):
            CONN.close()
        if (hasattr(cur,'close')):
            cur.close()
        #anyway reconnect
        CONN = get_connection()
        abort(500, "webserver err")
    finally:
        if (hasattr(cur,'close')):
            cur.close()

    return 'set ok'
    
run(host='124.173.70.227', port=37964)
