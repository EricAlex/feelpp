/* -*- mode: c++; coding: utf-8; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4; show-trailing-whitespace: t  -*- vim:set fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4

   This file is part of the Feel++ library

   Author(s): Christophe Prud'homme <christophe.prudhomme@feelpp.org>
   Date     : Tue Feb 25 12:13:15 2014

   Copyright (C) 2014 Feel++ Consortium

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <feel/feel.hpp>

int main(int argc, char**argv )
{
    //# marker1 #
    using namespace Feel;
	po::options_description qsnsoptions( "Quickstart Navier-Stokes options" );
	qsnsoptions.add_options()
		( "mu", po::value<double>()->default_value( 1.0 ), "coeff" )
		;
	Environment env( _argc=argc, _argv=argv,
                     _desc=qsnsoptions,
                     _about=about(_name="qs_ns",
                                  _author="Feel++ Consortium",
                                  _email="feelpp-devel@feelpp.org"));

    auto mesh = loadMesh( new Mesh<Simplex<2>> );
    CHECK( mesh->hasMarkers( {"wall","inlet"} ) ) << "Mesh markers wall or inlet are not set properly in "  << soption("gmsh.filename");
    auto Vh = THch<1>( mesh );
    auto U = Vh->element();
    auto V = Vh->element();
    auto u = U.element<0>();
    auto v = V.element<0>();
    auto p = U.element<1>();
    auto q = V.element<1>();

    auto deft = gradt( u );
    auto def = grad( v );
    double mu = doption(_name="mu");

    auto mybdf = bdf( _space=Vh, _name="mybdf" );

    auto ft = form1( _test=Vh );

    auto a = form2( _trial=Vh, _test=Vh), at = form2( _trial=Vh, _test=Vh);

    a = integrate( _range=elements( mesh ), _expr=mu*inner( deft, grad(v) ) + mybdf->polyDerivCoefficient(0)*trans(idt(u))*id(u) );
    a +=integrate( _range=elements( mesh ), _expr=-div( v )*idt( p ) - divt( u )*id( q ) );
    auto e = exporter( _mesh=mesh );

    for ( mybdf->start();  mybdf->isFinished() == false; mybdf->next(U) )
    {
        auto bdf_poly = mybdf->polyDeriv();
        auto rhsu =  bdf_poly.element<0>();
        auto extrap = mybdf->poly();
        auto extrapu = extrap.element<0>();
        ft = integrate( _range=elements(mesh), _expr=(trans(idv(rhsu))*id(u) ) );


        at = a;
        at += integrate( _range=elements( mesh ), _expr= trans(gradt(u)*idv(extrapu))*id(v) );
        at+=on(_range=markedfaces(mesh,"wall"), _rhs=ft, _element=u,
              _expr=zero<2>() );
        at+=on(_range=markedfaces(mesh,"inlet"), _rhs=ft, _element=u,
              _expr=-expr( soption(_name="functions.g")*N() );

        at.solve(_rhs=ft,_solution=U);


        e->step(mybdf->time())->add( "u", u );
        e->step(mybdf->time())->add( "p", p );
        e->save();


    }



    return 0;
}