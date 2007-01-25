/* -*- mode: c++; indent-tabs-mode: nil -*-
 *
 *  $Id: context_test.cpp,v 1.1 2006/10/09 07:07:59 Paul Pedersen Exp $
 *
 *	Copyright 2006-2007 FLWOR Foundation.
 *
 *  Author: Paul Pedersen
 *
 */

#include "context.h"
#include <typeinfo>

using namespace std;
using namespace xqp;

int main(int argc, char* argv[])
{
	try {
		context ctx;
		rchandle<QName> var1_h = new QName(QName::qn_var, "var1");
		rchandle<QName> var2_h = new QName(QName::qn_var, "var2");
		rchandle<QName> var3_h = new QName(QName::qn_var, "var3");

		rchandle<item_iterator> it1_h = new singleton_iterator(ctx,string("value-1"));
		rchandle<item_iterator> it2_h = new singleton_iterator(ctx,string("value-2"));
		rchandle<item_iterator> it3_h = new singleton_iterator(ctx,string("value-3"));

		// var 1
		rchandle<var_binding> vb1_h = new var_binding(var1_h, it1_h, item_type());
		ctx.push_var(vb1_h);
		rchandle<item_iterator> itv1_h = ctx.get_var_value(vb1_h->get_qname());
		item_iterator* itv1_p = &*itv1_h;
		if (itv1_p==NULL) {
			cout << "itv1_p==NULL, bailing\n";
			exit(-1);
		}
		vb1_h->get_qname()->put(cout,ctx) << " = ";
		while (!(itv1_p->done())) { 
			itv1_p->next()->put(cout,ctx) << endl;
		}

		// var 2
		rchandle<var_binding> vb2_h = new var_binding(var2_h, it2_h, item_type());
		ctx.push_var(vb2_h);
		rchandle<item_iterator> itv2_h = ctx.get_var_value(vb2_h->get_qname());
		item_iterator* itv2_p = &*itv2_h;
		if (itv2_p==NULL) {
			cout << "itv2_p==NULL, bailing\n";
			exit(-1);
		}
		vb2_h->get_qname()->put(cout,ctx) << " = ";
		while (!(itv2_p->done())) {
			itv2_p->next()->put(cout,ctx) << endl;
		}

		// shadow var1
		rchandle<var_binding> vb3_h = new var_binding(var1_h, it3_h, item_type());
		ctx.push_var(vb3_h);
		rchandle<item_iterator> itv3_h = ctx.get_var_value(vb3_h->get_qname());
		item_iterator* itv3_p = &*itv3_h;
		if (itv3_p==NULL) {
			cout << "itv3_p==NULL, bailing\n";
			exit(-1);
		}
		vb3_h->get_qname()->put(cout,ctx) << " = ";
		while (!(itv3_p->done())) {
			itv3_p->next()->put(cout,ctx) << endl;
		}

	} catch (exception& e) {
		cout << "exception: " << e.what() << endl;
	} catch (...) {
		cout << "...\n";
	}
}
