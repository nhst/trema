#
# Author: Nick Karanatsios <nickkaranatsios@gmail.com>
#
# Copyright (C) 2008-2011 NEC Corporation
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2, as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#


require File.join( File.dirname( __FILE__ ), "..", "spec_helper" )
require "trema"


describe ActionSetTpSrc do
  context "when an instance is created" do
    subject { ActionSetTpSrc.new( 5555 ) }
    its( :tp_src ) { should == 5555 }
    it "should print its attributes" do
      subject.inspect.should == "#<Trema::ActionSetTpSrc tp_port=5555>"
    end
    
    it "should append its action to a list of actions" do
      openflow_actions = double
      subject.should_receive( :append ).with( openflow_actions )
      subject.append( openflow_actions )
    end
  
    context "when tp_src argument is not supplied" do
      it "should raise an error" do
        lambda do
          ActionSetTpSrc.new
        end.should raise_error ArgumentError
      end
    end
  end
  
  
  context "when sending #flow_mod(add) with action set to tp src" do
    it "should have a flow with action set to mod_tp_src" do
      class FlowModAddController < Controller; end
      network {
        vswitch { datapath_id 0xabc }
      }.run( FlowModAddController ) {
        controller( "FlowModAddController" ).send_flow_mod_add( 0xabc,
          :actions => ActionSetTpSrc.new( 5555 ) )
        switch( "0xabc" ).should have( 1 ).flows
        switch( "0xabc" ).flows[0].actions.should match( /mod_tp_src:5555/ )
      }
    end
  end
end


### Local variables:
### mode: Ruby
### coding: utf-8-unix
### indent-tabs-mode: nil
### End:
