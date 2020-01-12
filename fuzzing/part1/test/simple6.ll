; ModuleID = 'simple6.c'
source_filename = "simple6.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@stdin = external dso_local global %struct._IO_FILE*, align 8

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 !dbg !7 {
entry:
  %retval = alloca i32, align 4
  %u1 = alloca i32, align 4
  %u2 = alloca i32, align 4
  %d = alloca i32, align 4
  %d1 = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %u1, metadata !11, metadata !DIExpression()), !dbg !12
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !13
  %call = call i32 @fgetc(%struct._IO_FILE* %0), !dbg !14
  store i32 %call, i32* %u1, align 4, !dbg !12
  call void @llvm.dbg.declare(metadata i32* %u2, metadata !15, metadata !DIExpression()), !dbg !16
  store i32 4, i32* %u2, align 4, !dbg !16
  call void @llvm.dbg.declare(metadata i32* %d, metadata !17, metadata !DIExpression()), !dbg !18
  %1 = load i32, i32* %u1, align 4, !dbg !19
  %cmp = icmp ne i32 %1, 0, !dbg !21
  br i1 %cmp, label %if.then, label %if.else, !dbg !22

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %u2, align 4, !dbg !23
  %3 = load i32, i32* %u1, align 4, !dbg !25
  %div = sdiv i32 %2, %3, !dbg !26
  store i32 %div, i32* %d, align 4, !dbg !27
  br label %if.end, !dbg !28

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %d1, metadata !29, metadata !DIExpression()), !dbg !31
  %4 = load i32, i32* %u2, align 4, !dbg !32
  %5 = load i32, i32* %u1, align 4, !dbg !33
  %add = add nsw i32 %5, 1, !dbg !34
  %div2 = sdiv i32 %4, %add, !dbg !35
  store i32 %div2, i32* %d1, align 4, !dbg !31
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i32 0, !dbg !36
}

; Function Attrs: nounwind readnone speculatable
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local i32 @fgetc(%struct._IO_FILE*) #2

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone speculatable }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5}
!llvm.ident = !{!6}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 8.0.0-3~ubuntu18.04.1 (tags/RELEASE_800/final)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, nameTableKind: None)
!1 = !DIFile(filename: "simple6.c", directory: "/home/cs6340/fuzzing/fuzzing/part1/test")
!2 = !{}
!3 = !{i32 2, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{!"clang version 8.0.0-3~ubuntu18.04.1 (tags/RELEASE_800/final)"}
!7 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 3, type: !8, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!8 = !DISubroutineType(types: !9)
!9 = !{!10}
!10 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!11 = !DILocalVariable(name: "u1", scope: !7, file: !1, line: 4, type: !10)
!12 = !DILocation(line: 4, column: 7, scope: !7)
!13 = !DILocation(line: 4, column: 18, scope: !7)
!14 = !DILocation(line: 4, column: 12, scope: !7)
!15 = !DILocalVariable(name: "u2", scope: !7, file: !1, line: 5, type: !10)
!16 = !DILocation(line: 5, column: 7, scope: !7)
!17 = !DILocalVariable(name: "d", scope: !7, file: !1, line: 5, type: !10)
!18 = !DILocation(line: 5, column: 15, scope: !7)
!19 = !DILocation(line: 6, column: 7, scope: !20)
!20 = distinct !DILexicalBlock(scope: !7, file: !1, line: 6, column: 7)
!21 = !DILocation(line: 6, column: 10, scope: !20)
!22 = !DILocation(line: 6, column: 7, scope: !7)
!23 = !DILocation(line: 7, column: 9, scope: !24)
!24 = distinct !DILexicalBlock(scope: !20, file: !1, line: 6, column: 16)
!25 = !DILocation(line: 7, column: 14, scope: !24)
!26 = !DILocation(line: 7, column: 12, scope: !24)
!27 = !DILocation(line: 7, column: 7, scope: !24)
!28 = !DILocation(line: 8, column: 3, scope: !24)
!29 = !DILocalVariable(name: "d", scope: !30, file: !1, line: 9, type: !10)
!30 = distinct !DILexicalBlock(scope: !20, file: !1, line: 8, column: 10)
!31 = !DILocation(line: 9, column: 9, scope: !30)
!32 = !DILocation(line: 9, column: 13, scope: !30)
!33 = !DILocation(line: 9, column: 19, scope: !30)
!34 = !DILocation(line: 9, column: 22, scope: !30)
!35 = !DILocation(line: 9, column: 16, scope: !30)
!36 = !DILocation(line: 11, column: 3, scope: !7)
