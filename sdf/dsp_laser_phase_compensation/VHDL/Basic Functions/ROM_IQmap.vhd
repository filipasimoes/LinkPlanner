library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
use std.textio.all;

entity ROM_IQmap is
GENERIC( 
       Data_width  : integer := 8;
	    Addr_width  : integer := 4;
	    Ntap_half   : integer :=11
  );
port (
	clk     : in std_logic;
	clk_en  : in std_logic;  
	Data1   : out std_logic_vector (Ntap_half*Data_width-1 DOWNTO 0);         
	Data2 	: out std_logic_vector (Ntap_half*Data_width-1 DOWNTO 0)        
	);
	
end ROM_IQmap;

architecture BEHAVIOR of ROM_IQmap is

	constant n_words: integer := 2**Addr_width;
	subtype memoryData is std_logic_vector(Data_width-1 DOWNTO 0);
	type tmemory is array (0 to n_words-1) of memoryData;
	
	--signal Aux_data1, Aux_data2 : std_logic_vector(Ntap_half * Data_width -1 DOWNTO 0):= (others => '0');
	
	impure function init_mem(mif_file_name : in string) return tmemory is
		file mif_file : text open read_mode is mif_file_name;
		variable mif_line : line;
		--variable temp_bit_v : bit_vector(Data_width-1 downto 0);
		variable temp_int_v : integer := 0;
		variable temp_mem : tmemory;
	begin
		for i in 0 to 15 loop
			readline(mif_file, mif_line);
			
			--read(mif_line, temp_bit_v);
			--temp_mem(i) := (to_stdlogicvector(temp_bit_v));
			
			read(mif_line, temp_int_v);
			temp_mem(i) := std_logic_vector(to_signed(temp_int_v, Data_width));
			
		end loop;
		return temp_mem;
	end function;
	
	constant s_tmemory1 : tmemory := init_mem("C:\Users\csmartins\Dropbox\_PhD\MyWorks\VHDL\Matlab Functions\IQMap_re.txt");
	constant s_tmemory2 : tmemory := init_mem("C:\Users\csmartins\Dropbox\_PhD\MyWorks\VHDL\Matlab Functions\IQMap_im.txt");

	begin -- BEHAVIOR
		process (Clk)
			variable Aux_data1, Aux_data2 : std_logic_vector(16 * Data_width -1 DOWNTO 0):= (others => '0');
			begin -- process
			if(rising_edge(Clk)) then
				if(clk_en = '1') then
					for i in 0 to 15 loop
						Aux_data1((i+1)*Data_width-1 downto i*Data_width) := s_tmemory1(i);
						Aux_data2((i+1)*Data_width-1 downto i*Data_width) := s_tmemory2(i);
						--aux := aux+1:
					end loop;
				end if;
			end if;
			Data1 <= Aux_data1;
			Data2 <= Aux_data2;
		end process;
	--Data1 <= Aux_data1;
	--Data2 <= Aux_data2;
	
end BEHAVIOR;