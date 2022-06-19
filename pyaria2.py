#!/bin/python3

import argparse
import code
import base64
import json
import sys
import urllib3
import xmlrpc.client
from pprint import pprint

URL_JSON = 'http://x200:6800/jsonrpc'
URL_XML  = 'http://x200:6800/rpc'


def getGlobalOption():

    s = xmlrpc.client.ServerProxy(URL_XML)
    r = s.aria2.getGlobalOption()
    pprint(r)


def call(d):

    encoded_data = json.dumps(d).encode('utf-8')

    http = urllib3.PoolManager()
    r = http.request('POST', URL_JSON, body=encoded_data, headers={'Content-Type': 'application/json'})

    assert type(s := r.data.decode('utf-8')) == str
    assert type(d := json.loads(s)) == dict
    pprint(d)


def download_torrent_yeet(path):

    call({
        'jsonrpc':'2.0',
        'id':'asdf',
        'method':'aria2.addTorrent',
        'params':[base64.b64encode(open(path, 'rb').read()).decode()]
    })


def saveSession():

    call({
        'jsonrpc':'2.0',
        'id':'asdf',
        'method':'aria2.saveSession',
    })


# aria2.tellActive
# aria2.tellWaiting
# aria2.tellStopped
def tellActive():

    s = xmlrpc.client.ServerProxy(URL_XML)
    r = s.aria2.tellActive()
    assert type(r) == list
    pprint(r)
    code.interact(local=locals())


def remove(gid):

    s = xmlrpc.client.ServerProxy(URL_XML)
    r = s.aria2.remove(gid)
    assert type(r) == str
    assert r == gid


def main():

    parser = argparse.ArgumentParser(description='x200 aria2 rpc client')

    # dest=
    # metavar=
    parser.add_argument('-o', '--option',  action='store_true', help='view global options')
    parser.add_argument('-s', '--save',    action='store_true', help='save session')
    parser.add_argument('-l', '--list',    action='store_true', help='list active downloads')
    parser.add_argument('-r', '--remove',  dest='GID',          help='remove a download')
    parser.add_argument('-t', '--torrent', metavar='FILE',      help='send and download torrent')

    args = parser.parse_args()

    if False:
        exit()

    elif args.option:
        getGlobalOption()
        exit()

    elif args.save:
        saveSession()
        exit()

    elif args.list:
        tellActive()
        exit()

    elif args.GID:
        remove(args.GID)
        exit()

    elif args.torrent:
        download_torrent_yeet(args.torrent)
        exit()

    else:
        parser.print_help()
        exit()


if __name__ == '__main__':
    main()
